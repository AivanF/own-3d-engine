/**
 * Copyright 2017, Barashev Ivan - All Rights Reserved.
 * Website: www.aivanf.com
 * This is proprietary software. Unauthorized commercial use of this code via any medium is strictly prohibited.
 * When use the code, you must give appropriate credit, provide a link to this license, and indicate if changes were made.
 * The work is provided "as is". You may not hold the author liable.
 */

#ifndef VIEWER_H
#define VIEWER_H

#include "item.h"

/// Viewer class acts as both camera and scene.
class Viewer {
public:
    QVector<Model*> mdls;
    QVector<Item*> items;
    float ry, rx, sc;
    bool usePerspective, useRoberts, useZbuffer;
    float **zbuf;
    float ambient, power;
    int intensity;
    // 0 - edges, 1 - Goraund, 2 - Phong
    int filling;

    QPixmap image1;
    QPixmap image2;
    QPainter *ipainter1;
    QPainter *ipainter2;

    Viewer(int w, int h);

    bool canSee(QVector3D norm);
    QColor getPointLight(QVector3D point, QVector3D normal);
    int process();
};

#endif // VIEWER_H
