/**
 * Copyright 2017, Barashev Ivan - All Rights Reserved.
 * Website: www.aivanf.com
 * This is proprietary software. Unauthorized commercial use of this code via any medium is strictly prohibited.
 * When use the code, you must give appropriate credit, provide a link to this license, and indicate if changes were made.
 * The work is provided "as is". You may not hold the author liable.
 */

#ifndef MODEL_H
#define MODEL_H

#include <QVector>
#include <QPoint>
#include <QVector3D>
#include <QGenericMatrix>
#include <QPainter>

class Viewer;

/// Model describes vertices, edges and triagles of a solid.
/// Can be drawn from an Item. Can be loaded from a file or saved to.
class Model {
public:
    /// 3D positions of points
    QVector<QVector3D> pnts;
    /// Normals for all the points
    QVector<QVector3D> pnorm;
    /// Triangles with points indices in x, y and width
    QVector<QRect> trs;
    /// Normals for all the triangles
    QVector<QVector3D> tnorm;
    /// Colors for drawing
    QColor clr;


    Model();

    void addPoint(QVector3D point);
    void addTria(QRect tria);
    void normalize(QVector<QVector3D> &news);

    void saveTo(QString fname);
    void loadFrom(QString fname);

    /// Draws the
    void drawUsual(QMatrix4x4 mod, QPainter &painter, Viewer *v);
    void drawZbuf(QMatrix4x4 mod, QPainter &painter, Viewer *v);

    void drawTria(QVector3D a, QVector3D b, QVector3D c, QPainter &painter);
};

#endif // MODEL_H
