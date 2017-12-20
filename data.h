/**
 * Copyright 2017, Barashev Ivan - All Rights Reserved.
 * Website: www.aivanf.com
 * This is proprietary software. Unauthorized commercial use of this code via any medium is strictly prohibited.
 * When use the code, you must give appropriate credit, provide a link to this license, and indicate if changes were made.
 * The work is provided "as is". You may not hold the author liable.
 */

#ifndef DATA_H
#define DATA_H

/**
  * Functions to create different solids.
  */

#include "model.h"

Model* createTetrahedron(QVector<Model*> &mdls);
Model* createOctahedron(QVector<Model*> &mdls);
Model* createHexahedron(QVector<Model*> &mdls);
Model* createIcosahedron(QVector<Model*> &mdls);
Model* createDodecahedron(QVector<Model*> &mdls);
Model* createSphere(QVector<Model*> &mdls, Model *Icosahedron, int rec);
Model* createGarlic(QVector<Model*> &mdls, Model *Sphere);
Model* createTorus(QVector<Model*> &mdls, int counts, float ro, float ri, int turns, float addheight, float addwidth);

#endif // DATA_H
