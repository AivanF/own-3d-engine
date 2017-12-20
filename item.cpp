/**
 * Copyright 2017, Barashev Ivan - All Rights Reserved.
 * Website: www.aivanf.com
 * This is proprietary software. Unauthorized commercial use of this code via any medium is strictly prohibited.
 * When use the code, you must give appropriate credit, provide a link to this license, and indicate if changes were made.
 * The work is provided "as is". You may not hold the author liable.
 */

#include "item.h"
#include "helper.h"
#include <QDebug>

int item_ids = 0;

Item::Item() {
    id = item_ids++;
    mdl = nullptr;
    mx = 0; my = 0; mz = 0;
    rx = 0; ry = 0; rz = 0;
}

Item::Item(Model* m) {
    id = item_ids++;
    mdl = m;
    mx = 0; my = 0; mz = 0;
    rx = 0; ry = 0; rz = 0;
}

Item::Item(Model* m, float x, float y, float z) {
    id = item_ids++;
    mdl = m;
    mx = x; my = y; mz = z;
    rx = 0; ry = 0; rz = 0;
}

void Item::drawUsual(QMatrix4x4 mod, QPainter &painter, Viewer *v) {
    if (mdl) {
        QMatrix4x4 ct = rotateX(rx);
        ct = ct * rotateY(ry);
        ct = ct * rotateZ(rz);
        ct = ct * shift(mx, my, mz);
        ct = ct * mod;
        mdl->drawUsual(ct, painter, v);
    }
}

void Item::drawZbuf(QMatrix4x4 mod, QPainter &painter, Viewer *v) {
    if (mdl) {
        QMatrix4x4 ct = rotateX(rx);
        ct = ct * rotateY(ry);
        ct = ct * rotateZ(rz);
        ct = ct * shift(mx, my, mz);
        ct = ct * mod;
        mdl->drawZbuf(ct, painter, v);
    }
}
