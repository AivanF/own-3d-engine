/**
 * Copyright 2017, Barashev Ivan - All Rights Reserved.
 * Website: www.aivanf.com
 * This is proprietary software. Unauthorized commercial use of this code via any medium is strictly prohibited.
 * When use the code, you must give appropriate credit, provide a link to this license, and indicate if changes were made.
 * The work is provided "as is". You may not hold the author liable.
 */

#ifndef UTILS_H
#define UTILS_H

#include <QMatrix4x4>

/**
  * Some helpful math and other functions.
  */

#pragma mark Different

float gradus(float x);
int forRGB(float x);
int toRGB(float x);
QColor adjColor(QColor clr, float cf);
QColor sumColors(QColor a, QColor b, QColor c);


#pragma mark Matrices general

QMatrix4x4 identify();
QMatrix4x4 compress(QVector<QMatrix4x4> mods);
QMatrix4x4 multiple(QMatrix4x4 left, QMatrix4x4 right);
QVector3D multiple(QVector4D left, QMatrix4x4 right);
// Just an alias.
QVector3D multiple(QVector3D left, QMatrix4x4 right);
// Returns transformed points.
QVector<QVector3D> apply(QVector<QVector3D> &pnts, QMatrix4x4 mod);


#pragma mark Matrices generators

QMatrix4x4 scale(float x);
QMatrix4x4 scale(float x, float y, float z);
QMatrix4x4 rotateX(float angle);
QMatrix4x4 rotateY(float angle);
QMatrix4x4 rotateZ(float angle);
QMatrix4x4 shift(float x, float y, float z);
QMatrix4x4 perspective(float z);


#pragma mark Vectors
// Returns if tria is visible.
bool canSee(QVector3D norm);
// Determinant of the matrix formed from the column vectors u and v.
float det(QVector2D u, QVector2D v);
// Just an alias.
float det(QVector3D u, QVector3D v);
// Vector normalisation, makes length equal 1
QVector3D normalize(float x, float y, float z);
// Just an alias.
QVector3D normalize(QVector3D a);
// Returns normal for a plane.
QVector3D normalto(QVector3D v0, QVector3D v1, QVector3D v2);
// Returns reflected vector of a by n.
QVector3D reflected(QVector3D a, QVector3D n);
// Vectors dot product.
float dotproduct(QVector3D a, QVector3D b);
// Returns middle of 2 vectors.
QVector3D middle(QVector3D a, QVector3D b);
// Returns middle of 3 vectors.
QVector3D middle(QVector3D a, QVector3D b, QVector3D c);


#pragma mark Printing

void print(QVector3D);
void print(QVector4D);
void print(QMatrix4x4);

#endif // UTILS_H
