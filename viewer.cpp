/**
 * Copyright 2017, Barashev Ivan - All Rights Reserved.
 * Website: www.aivanf.com
 * This is proprietary software. Unauthorized commercial use of this code via any medium is strictly prohibited.
 * When use the code, you must give appropriate credit, provide a link to this license, and indicate if changes were made.
 * The work is provided "as is". You may not hold the author liable.
 */

#include <QTime>
#include <QtMath>

#include "viewer.h"
#include "helper.h"

Viewer::Viewer(int w, int h) {
    ry = 200; rx = 100;
    sc = 1.0;
    intensity = 2;
    power = 4.0f;
    ambient = 0.1f;
    filling = 0;

    image1 = QPixmap(w, h);
    image2 = QPixmap(w/2, h/2);
    ipainter1 = new QPainter(&image1);
    ipainter1->setRenderHint(QPainter::Antialiasing);
    ipainter2 = new QPainter(&image2);
    ipainter2->setRenderHint(QPainter::Antialiasing);
    zbuf = new float*[image2.width()];
    for (int i = 0; i < image2.width(); i++)
        zbuf[i] = new float[image2.height()];
}

bool greaterThan(const Item* e1, const Item* e2) {
    return e1->tz > e2->tz;
}

bool lessThan(const Item* e1, const Item* e2) {
    return e1->tz > e2->tz;
}

QMatrix4x4 ct;
QVector3D _sight(0, 0, 1);
QVector3D _light;

bool Viewer::canSee(QVector3D norm) {
    if (useRoberts) {
        return 0 < dotproduct(norm, _sight);
    }
    return true;
}

QColor Viewer::getPointLight(QVector3D point, QVector3D normal) {
    point = point - _light;
    point.setZ(-point.z());
    float dst = point.length() / 10.0f;
    dst = std::min(1.0f, intensity * 500.0f / (dst*dst));
    point = normalize(point);
    float r = (1 - dotproduct(normal, point)) / 2;
    r *= ambient + std::min(1.0f-ambient, dst);
    float g = (1 + dotproduct(reflected(point, normal), _sight)) / 2;
    g = std::pow(g, power);
    g *= dst;
    return QColor(toRGB(r + g), toRGB(g), toRGB(g));
}

int Viewer::process() {

    ct = identify();
    ct = ct * scale(sc);
    ct = ct * rotateX(rx);
    ct = ct * rotateY(ry);
    int shx = image1.width() / 2;
    int shy = image1.height() / 2;
    ct = ct * shift(shx, shy, 0);
    if (usePerspective) {
        ct = ct * perspective(1.0f / (1000 * sc));
    }
    for (int i = 0; i < items.length(); i++) {
        QVector3D v = multiple(QVector3D(items[i]->mx, items[i]->my, items[i]->mz), ct);
        items[i]->tx = v.x();
        items[i]->ty = v.y();
        items[i]->tz = v.z();
    }
    _light = QVector3D(shx, shy, -100 -300 / sc);

    QTime myTimer;
    myTimer.start();
    if (!useZbuffer) {
        //          Usual drawing
        ipainter1->fillRect(0, 0, image1.width(), image1.height(), QColor(0, 0, 0));
        qSort (items.begin(), items.end(), greaterThan);
        for (int i = 0; i < items.length(); i++) {
            if (items[i]->tz > -500 && items[i]->tx > 0 && items[i]->ty > 0 && items[i]->tx < image1.width() && items[i]->ty < image1.height())
                items[i]->drawUsual(ct, *ipainter1, this);
        }
    } else {
        //          Z-buffering
        ipainter2->fillRect(0, 0, image2.width(), image2.height(), QColor(0, 0, 0));
        for (int xx = 0; xx < image2.width(); xx++) {
            for (int yy = 0; yy < image2.height(); yy++) {
                zbuf[xx][yy] = 9999;
            }
        }
        qSort (items.begin(), items.end(), lessThan);
        for (int i = 0; i < items.length(); i++) {
            if (items[i]->tz > -500 && items[i]->tx > 0 && items[i]->ty > 0 && items[i]->tx < image1.width() && items[i]->ty < image1.height()) {
                items[i]->drawZbuf(ct, *ipainter2, this);
            }
        }
    }
    return myTimer.elapsed();
}
