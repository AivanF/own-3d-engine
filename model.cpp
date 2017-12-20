/**
 * Copyright 2017, Barashev Ivan - All Rights Reserved.
 * Website: www.aivanf.com
 * This is proprietary software. Unauthorized commercial use of this code via any medium is strictly prohibited.
 * When use the code, you must give appropriate credit, provide a link to this license, and indicate if changes were made.
 * The work is provided "as is". You may not hold the author liable.
 */

#include <QtGlobal>
#include <QtMath>
#include <QPainterPath>
#include <QTextCodec>
#include <QFile>

#include "model.h"
#include "helper.h"
#include "viewer.h"


Model::Model() {
    clr = QColor(80, 100, 120);
}

void Model::addPoint(QVector3D point) {
    pnts.append(point);
}

void Model::addTria(QRect tria) {
    // --- Order correction --- //
//    if (pnts.length() > tria.x() && pnts.length() > tria.y() && pnts.length() > tria.width()) {
//        QVector3D a = pnts[tria.x()];
//        QVector3D b = pnts[tria.y()];
//        QVector3D c = pnts[tria.width()];
//        // vector to the middle
//        QVector3D m = middle(a, b, c);
//        // check normal
//        float sign = dotproduct(normalto(a, b, c), m);
//        if (sign < 0) {
//            // reverse points
//            QRect old = tria;
//            tria = QRect(old.width(), old.y(), old.x(), -1);
//        }
//    }

    trs.append(tria);
}

void Model::normalize(QVector<QVector3D> &news) {
    {
        tnorm.clear();
        for (int i = 0; i < trs.length(); i++) {
            tnorm.append(normalto(news[trs[i].x()], news[trs[i].y()], news[trs[i].width()]));
        }
    }
    {
        pnorm.clear();
        int cnts[pnts.length()];
        for (int i = 0; i < pnts.length(); i++) {
            cnts[i] = 0;
        }
        QVector3D vs[pnts.length()];
        for (int i = 0; i < trs.length(); i++) {
            cnts[trs[i].x()]++;
            cnts[trs[i].y()]++;
            cnts[trs[i].width()]++;
            vs[trs[i].x()] += tnorm[i];
            vs[trs[i].y()] += tnorm[i];
            vs[trs[i].width()] += tnorm[i];
        }
        for (int i = 0; i < pnts.length(); i++) {
            pnorm.append(vs[i] * (1.0f / cnts[i]));
        }
    }
}


void Model::saveTo(QString fname) {
    QFile file(fname);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    for (int i = 0; i < trs.length(); i++) {
        out << "1 " << trs[i].x() << " " << trs[i].y() << " " << trs[i].width() << "\n";
    }
    for (int i = 0; i < pnts.length(); i++) {
        out << "0 " << pnts[i].x() << " " << pnts[i].y() << " " << pnts[i].z() << "\n";
    }
    file.close();
}

void Model::loadFrom(QString fname) {
    QFile file(fname);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            QString str = QTextCodec::codecForMib(106)->toUnicode(line);
            str = str.remove(str.length() - 1, 1);
            QStringList pieces = str.split(" ");
            if (pieces.length() > 3) {
                if (pieces.value(0) == "1") {
                    addTria( QRect(pieces.value(1).toFloat(), pieces.value(2).toFloat(), pieces.value(3).toFloat(), -1) );
                } else if (pieces.value(0) == "0") {
                    addPoint( QVector3D(pieces.value(1).toFloat(), pieces.value(2).toFloat(), pieces.value(3).toFloat()) );
                }
            }
        }
    }
}

void Model::drawTria(QVector3D a, QVector3D b, QVector3D c, QPainter &painter) {
    QPainterPath path;
    path.moveTo (a.x(), a.y());
    path.lineTo (b.x(), b.y());
    path.lineTo (c.x(), c.y());
    path.lineTo (a.x(), a.y());
    painter.setPen (Qt::NoPen);
    painter.fillPath (path, QBrush (clr));

    painter.setPen (QPen(QColor(230, 245, 255)));
    painter.drawLine (a.x(), a.y(), b.x(), b.y());
    painter.drawLine (a.x(), a.y(), c.x(), c.y());
    painter.drawLine (c.x(), c.y(), b.x(), b.y());
}

void Model::drawUsual(QMatrix4x4 mod, QPainter &painter, Viewer *viewer) {
    QVector<QVector3D> news = apply(pnts, mod);
    normalize(news);
    for (int i = 0; i < trs.length(); i++) {
        QRect t = trs[i];
        if (viewer->canSee(tnorm[i])) {
            drawTria(news[t.x()], news[t.y()], news[t.width()], painter);
        }
    }
}

float len2(QVector3D v) {
    return sqrt(v.x()*v.x()+v.y()*v.y());
}

void Model::drawZbuf(QMatrix4x4 mod, QPainter &painter, Viewer *viewer) {
    QColor clr, clr0, clr1, clr2;
    QVector<QVector3D> news = apply(pnts, mod);
    normalize(news);
    for (int i = 0; i < trs.length(); i++) {
        QRect t = trs[i];
        QVector3D v0 = news[t.x()];
        QVector3D v1 = news[t.y()];
        QVector3D v2 = news[t.width()];
        int xmax = std::max((int)v0.x(), std::max((int)v1.x(), (int)v2.x()));
        int xmin = std::min((int)v0.x(), std::min((int)v1.x(), (int)v2.x()));
        int ymax = std::max((int)v0.y(), std::max((int)v1.y(), (int)v2.y()));
        int ymin = std::min((int)v0.y(), std::min((int)v1.y(), (int)v2.y()));
        if (viewer->canSee(tnorm[i])) {
            if (viewer->filling == 0) {
                // Edges
                clr = viewer->getPointLight(middle(v0, v1, v2), pnorm[t.x()]);
            } else if (viewer->filling == 1) {
                // Goraud
                clr0 = viewer->getPointLight(v0, pnorm[t.x()]);
                clr1 = viewer->getPointLight(v1, pnorm[t.y()]);
                clr2 = viewer->getPointLight(v2, pnorm[t.width()]);
            }
            v1 -= v0; v2 -= v0;
            float pr = 1 / (len2(v1) + len2(v2));
            for (int xxx = 0; xxx < viewer->image2.width(); xxx++) {
                int xx = xxx*2;
                for (int yyy = 0; yyy < viewer->image2.height(); yyy++) {
                    int yy = yyy*2;
                    if (yy >= ymin && yy <= ymax && xx >= xmin && xx <= xmax) {
                        QVector3D v(xx, yy, -1);
                        float a = (det(v, v2) - det(v0, v2)) / det(v1, v2);
                        float b = (det(v0, v1) - det(v, v1)) / det(v1, v2);
                        if (a >= 0 && b >= 0 && (a+b < 1.0 + pr)) {
                            v.setZ( v0.z() + v1.z() * a + v2.z() * b );
                            if (v.z() < viewer->zbuf[xxx][yyy]) {
                                viewer->zbuf[xxx][yyy] = v.z();
                                float c = std::max(1.0f - a - b, 0.0f);
//                                clr.setRgb(toRGB(a), toRGB(b), toRGB(c));
                                if (viewer->filling == 2) {
                                    // Phong
                                    clr = viewer->getPointLight(v, c * pnorm[t.x()] + a * pnorm[t.y()] + b * pnorm[t.width()]);
                                } else if (viewer->filling == 1) {
                                    // Goraud
                                    clr = sumColors(adjColor(clr0, c), adjColor(clr1, a), adjColor(clr2, b));
                                }
                                painter.fillRect(xxx, yyy, 1, 1, clr);
                            }
                        }
                    }
                }
            }
        }
    }
}


