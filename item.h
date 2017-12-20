/**
 * Copyright 2017, Barashev Ivan - All Rights Reserved.
 * Website: www.aivanf.com
 * This is proprietary software. Unauthorized commercial use of this code via any medium is strictly prohibited.
 * When use the code, you must give appropriate credit, provide a link to this license, and indicate if changes were made.
 * The work is provided "as is". You may not hold the author liable.
 */

#ifndef ITEM_H
#define ITEM_H


#include "model.h"

class Viewer;

/// Item is a scene object, it is linked with a model and has some own geometric attributes.
class Item {
public:
    Item();
    Item(Model* m);
    Item(Model* m, float x, float y, float z);

    Model *mdl;
    /// My position
    float mx, my, mz;
    /// Rotation
    int rx, ry, rz;
    /// True position - transformed My
    float tx, ty, tz;
    /// ID
    int id;

    void drawUsual(QMatrix4x4 mod, QPainter &painter, Viewer *v);
    void drawZbuf(QMatrix4x4 mod, QPainter &painter, Viewer *v);
};

#endif // ITEM_H
