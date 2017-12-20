/**
 * Copyright 2017, Barashev Ivan - All Rights Reserved.
 * Website: www.aivanf.com
 * This is proprietary software. Unauthorized commercial use of this code via any medium is strictly prohibited.
 * When use the code, you must give appropriate credit, provide a link to this license, and indicate if changes were made.
 * The work is provided "as is". You may not hold the author liable.
 */

#include "helper.h"
#include <QDebug>
#include <QColor>
#include <QString>
#include <QtMath>
#include <QVector2D>


#pragma mark Different

float gradus(float x) {
    if (x > 360) {
        return x - 360;
    } else if (x < 0) {
        return x + 360;
    } else {
        return x;
    }
}

int forRGB(float x) {
    return std::max(std::min((int)x, 255), 0);
}

int toRGB(float x) {
    return forRGB(255.0 * x);
}

QColor adjColor(QColor clr, float cf) {
    return QColor(forRGB(clr.red() * cf), forRGB(clr.green() * cf), forRGB(clr.blue() * cf));
}

QColor sumColors(QColor a, QColor b, QColor c) {
    return QColor(forRGB(a.red() + b.red() + c.red()), forRGB(a.green() + b.green() + c.green()), forRGB(a.blue() + b.blue() + c.blue()));
}



#pragma mark Matrices general

float goodmat[16] = {1, 0, 0, 0,
                     0, 1, 0, 0,
                     0, 0, 1, 0,
                     0, 0, 0, 1 };

QMatrix4x4 identify() {
    return QMatrix4x4(goodmat);
}

QMatrix4x4 compress(QVector<QMatrix4x4> mods) {
    QMatrix4x4 proc = identify();
    for (int i = 0; i < mods.length(); i++) {
        proc = multiple(proc, mods[i]);
    }
    return proc;
}

QMatrix4x4 multiple(QMatrix4x4 left, QMatrix4x4 right) {
    float vals[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    float k;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            k = 0;
            for (int t = 0; t < 4; t++) {
                float m = left.constData()[t * 4 + i];
                float n = right.constData()[j * 4 + t];
                k += m * n;
            }
            vals[i * 4 + j] = k;
        }
    }
    return QMatrix4x4(vals);
//    return left * right;
}

QVector3D multiple(QVector3D left, QMatrix4x4 right) {
    return multiple(QVector4D(left.x(), left.y(), left.z(), 1), right);
}

QVector3D multiple(QVector4D left, QMatrix4x4 right) {
    float v[4] = {0, 0, 0, 0};
    for (int p = 0; p < 4; p++) {
        for (int t = 0; t < 4; t++) {
            float ch = right.constData()[p * 4 + (3 - t)] * left[3 - t];
            v[p] += ch;
        }
    }
    /*
     *
     *          // --- Devide by 4th coordinate! --- //
     *
     *
     */
    return QVector3D(v[0] / v[3], v[1] / v[3], v[2] / v[3]);
}

QVector<QVector3D> apply(QVector<QVector3D> &pnts, QMatrix4x4 mod) {
    QVector<QVector3D> res;
    for (int i = 0; i < pnts.length(); i++) {
        float s[4] = { pnts[i].x(), pnts[i].y(), pnts[i].z(), 1 };
        res.append( multiple(QVector4D(s[0], s[1], s[2], s[3]), mod) );
    }
    return res;
}



#pragma mark Matrices generators


QMatrix4x4 scale(float x) {
    return scale(x, x, x);
}

QMatrix4x4 scale(float x, float y, float z) {
    float vals[16] = {
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1,
    };
    return QMatrix4x4(vals);
}

QMatrix4x4 rotateX(float angle) {
    float c = qCos(qDegreesToRadians(angle));
    float s = qSin(qDegreesToRadians(angle));
    float vals[16] = {
        1, 0,  0, 0,
        0, c,  s, 0,
        0, -s, c, 0,
        0, 0,  0, 1,
    };
    return QMatrix4x4(vals);
}

QMatrix4x4 rotateY(float angle) {
    float c = qCos(qDegreesToRadians(angle));
    float s = qSin(qDegreesToRadians(angle));
    float vals[16] = {
        c, 0, -s, 0,
        0, 1,  0, 0,
        s, 0,  c, 0,
        0, 0,  0, 1,
    };
    return QMatrix4x4(vals);
}

QMatrix4x4 rotateZ(float angle) {
    float c = qCos(qDegreesToRadians(angle));
    float s = qSin(qDegreesToRadians(angle));
    float vals[16] = {
        c,  s, 0, 0,
        -s, c, 0, 0,
        0,  0, 1, 0,
        0,  0,  0, 1,
    };
    return QMatrix4x4(vals);
}

QMatrix4x4 shift(float x, float y, float z) {
    float vals[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        x, y, z, 1,
    };
    return QMatrix4x4(vals);
}

QMatrix4x4 perspective(float z) {
    float vals[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, z,
        0, 0, 0, 1,
    };
    return QMatrix4x4(vals);
}



#pragma mark Vectors

float det(QVector2D u, QVector2D v) {
    return u.x() * v.y() - u.y() * v.x();
}

float det(QVector3D u, QVector3D v) {
    return det(QVector2D(u.x(), u.y()), QVector2D(v.x(), v.y()));
}

QVector3D normalize(float x, float y, float z) {
    float len = sqrt( x*x + y*y + z*z );
    return QVector3D( x / len, y / len, z / len );
}

QVector3D normalize(QVector3D a) {
    return normalize( a.x(), a.y(), a.z() );
}

QVector3D normalto(QVector3D v0, QVector3D v1, QVector3D v2) {
    QVector3D a = v1 - v0;
    QVector3D b = v2 - v0;
    float nx = a.y() * b.z() - a.z() * b.y();
    float ny = a.z() * b.x() - a.x() * b.z();
    float nz = a.x() * b.y() - a.y() * b.x();
    return normalize( nx, ny, nz );
}

QVector3D reflected(QVector3D a, QVector3D n) {
    return a - 2 * n * dotproduct(a, n);
}

float dotproduct(QVector3D a, QVector3D b) {
    return a.x()*b.x() + a.y()*b.y() + a.z()*b.z();
}

QVector3D middle(QVector3D a, QVector3D b) {
    return QVector3D ((a.x() + b.x()) / 2, (a.y() + b.y()) / 2, (a.z() + b.z()) / 2);
}

QVector3D middle(QVector3D a, QVector3D b, QVector3D c) {
    return QVector3D ((a.x() + b.x() + c.x()) / 3, (a.y() + b.y() + c.y()) / 3, (a.z() + b.z() + c.z()) / 3);
}



#pragma mark Printing


void print(QVector3D v) {
    qDebug() << "- Vector:";
    QString row = "";
    for (int i = 0; i < 3; i++) {
        row += " " + QString::number(v[i]);
    }
    qDebug() << row;
}

void print(QVector4D v) {
    qDebug() << "- Vector:";
    QString row = "";
    for (int i = 0; i < 4; i++) {
        row += " " + QString::number(v[i]);
    }
    qDebug() << row;
}

void print(QMatrix4x4 m) {
    qDebug() << "- Matrix:";
    for (int i = 0; i < 4; i++) {
        QString row = "";
        for (int j = 0; j < 4; j++) {
            row = row + " " + QString::number(m.constData()[i + j * 4]);
        }
        qDebug() << row;
    }
}
