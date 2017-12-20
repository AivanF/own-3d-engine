/**
 * Copyright 2017, Barashev Ivan - All Rights Reserved.
 * Website: www.aivanf.com
 * This is proprietary software. Unauthorized commercial use of this code via any medium is strictly prohibited.
 * When use the code, you must give appropriate credit, provide a link to this license, and indicate if changes were made.
 * The work is provided "as is". You may not hold the author liable.
 */

#include <QtMath>
#include "data.h"
#include "helper.h"

/*
 * Helpful link:
 *    http://paulbourke.net/geometry/platonic/
 */

Model* createTetrahedron(QVector<Model*> &mdls) {
    Model *m = new Model();
    m->addPoint(QVector3D(20, 20, 20));
    m->addPoint(QVector3D(-20, 20, -20));
    m->addPoint(QVector3D(20, -20, -20));
    m->addPoint(QVector3D(-20, -20, 20));
    m->addTria(QRect(0, 1, 2, -1));
    m->addTria(QRect(1, 3, 2, -1));
    m->addTria(QRect(0, 2, 3, -1));
    m->addTria(QRect(0, 3, 1, -1));
    mdls.append(m);
    m->saveTo("tetra.mdl.txt");
    return m;
}

Model* createOctahedron(QVector<Model*> &mdls) {
    Model *m = new Model();
    float a = 20 / sqrt(2), b = 20;
    m->addPoint(QVector3D(-a, 0, -a));
    m->addPoint(QVector3D(a, 0, -a));
    m->addPoint(QVector3D(a, 0, a));
    m->addPoint(QVector3D(-a, 0, a));
    m->addPoint(QVector3D(0, b, 0));
    m->addPoint(QVector3D(0, -b, 0));
    m->addTria(QRect(0, 1, 4, -1));
    m->addTria(QRect(1, 0, 5, -1));
    m->addTria(QRect(1, 2, 4, -1));
    m->addTria(QRect(2, 1, 5, -1));
    m->addTria(QRect(2, 3, 4, -1));
    m->addTria(QRect(3, 2, 5, -1));
    m->addTria(QRect(3, 0, 4, -1));
    m->addTria(QRect(0, 3, 5, -1));
    mdls.append(m);
    m->saveTo("octa.mdl.txt");
    return m;
}

Model* createHexahedron(QVector<Model*> &mdls) {
    Model *m = new Model();
    m->addPoint(QVector3D(-20, -20, -20));
    m->addPoint(QVector3D(-20, -20, 20));
    m->addPoint(QVector3D(-20, 20, -20));
    m->addPoint(QVector3D(-20, 20, 20));
    m->addPoint(QVector3D(20, -20, -20));
    m->addPoint(QVector3D(20, -20, 20));
    m->addPoint(QVector3D(20, 20, -20));
    m->addPoint(QVector3D(20, 20, 20));

    // same X
    m->addTria(QRect(0, 2, 3, -1));
    m->addTria(QRect(3, 1, 0, -1));
    m->addTria(QRect(4, 5, 7, -1));
    m->addTria(QRect(7, 6, 4, -1));
    // same Z
    m->addTria(QRect(5, 1, 3, -1));
    m->addTria(QRect(3, 7, 5, -1));
    m->addTria(QRect(2, 0, 4, -1));
    m->addTria(QRect(4, 6, 2, -1));
    // same Y
    m->addTria(QRect(7, 3, 2, -1));
    m->addTria(QRect(2, 6, 7, -1));
    m->addTria(QRect(4, 0, 1, -1));
    m->addTria(QRect(1, 5, 4, -1));

    mdls.append(m);
    m->saveTo("box.mdl.txt");
    return m;
}

Model* createIcosahedron(QVector<Model*> &mdls) {
    Model *m = new Model();
    float phi = (1 + sqrt(5)) / 2;
    float a = 20;
    float b = 20 / phi;

    m->addPoint(QVector3D(0, b, a));
    m->addPoint(QVector3D(0, b, -a));
    m->addPoint(QVector3D(0, -b, a));
    m->addPoint(QVector3D(0, -b, -a));

    m->addPoint(QVector3D(b, a, 0));
    m->addPoint(QVector3D(b, -a, 0));
    m->addPoint(QVector3D(-b, a, 0));
    m->addPoint(QVector3D(-b, -a, 0));

    m->addPoint(QVector3D(a, 0, b));
    m->addPoint(QVector3D(a, 0, -b));
    m->addPoint(QVector3D(-a, 0, b));
    m->addPoint(QVector3D(-a, 0, -b));

    m->addTria(QRect(1, 4, 6, -1));
    m->addTria(QRect(0, 6, 4, -1));
    m->addTria(QRect(0, 2, 10, -1));
    m->addTria(QRect(0, 8, 2, -1));

    m->addTria(QRect(1, 3, 9, -1));
    m->addTria(QRect(1, 11, 3, -1));
    m->addTria(QRect(2, 5, 7, -1));
    m->addTria(QRect(3, 7, 5, -1));

    m->addTria(QRect(6, 10, 11, -1));
    m->addTria(QRect(7, 11, 10, -1));
    m->addTria(QRect(4, 9, 8, -1));
    m->addTria(QRect(5, 8, 9, -1));

    m->addTria(QRect(0, 10, 6, -1));
    m->addTria(QRect(0, 4, 8, -1));
    m->addTria(QRect(1, 6, 11, -1));
    m->addTria(QRect(1, 9, 4, -1));

    m->addTria(QRect(3, 11, 7, -1));
    m->addTria(QRect(3, 5, 9, -1));
    m->addTria(QRect(2, 7, 10, -1));
    m->addTria(QRect(2, 8, 5, -1));

    mdls.append(m);
    m->saveTo("isoc.mdl.txt");
    return m;
}




void addFive(Model *m, int p1, int p2, int p3, int p4, int p5) {
//    qDebug() << p1 << p2 << p3 << p4 << p5;
    m->addTria(QRect(p1, p2, p3, -1));
    m->addTria(QRect(p3, p4, p1, -1));
    m->addTria(QRect(p4, p5, p1, -1));
}

Model* createDodecahedron(QVector<Model*> &mdls) {
    Model *m = new Model();
    float phi = (1 + sqrt(5)) / 2;
    float c = 40 - 20 * phi;
    float b = 20 / phi;
    float a = 20;

    m->addPoint(QVector3D(0, a, c));
    m->addPoint(QVector3D(0, a, -c));
    m->addPoint(QVector3D(0, -a, c));
    m->addPoint(QVector3D(0, -a, -c));

    m->addPoint(QVector3D(c, 0, a));
    m->addPoint(QVector3D(c, 0, -a));
    m->addPoint(QVector3D(-c, 0, a));
    m->addPoint(QVector3D(-c, 0, -a));

    m->addPoint(QVector3D(a, c, 0));
    m->addPoint(QVector3D(a, -c, 0));
    m->addPoint(QVector3D(-a, c, 0));
    m->addPoint(QVector3D(-a, -c, 0));

    m->addPoint(QVector3D(b, b, b));
    m->addPoint(QVector3D(b, b, -b));
    m->addPoint(QVector3D(b, -b, b));
    m->addPoint(QVector3D(b, -b, -b));

    m->addPoint(QVector3D(-b, b, b));
    m->addPoint(QVector3D(-b, b, -b));
    m->addPoint(QVector3D(-b, -b, b));
    m->addPoint(QVector3D(-b, -b, -b));

    addFive(m, 4, 6, 16, 0, 12);
    addFive(m, 6, 4, 14, 2, 18);
    addFive(m, 5, 7, 19, 3, 15);
    addFive(m, 7, 5, 13, 1, 17);

    addFive(m, 1, 0, 12, 8, 13);
    addFive(m, 0, 1, 17, 10, 16);
    addFive(m, 3, 2, 18, 11, 19);
    addFive(m, 2, 3, 15, 9, 14);

    addFive(m, 8, 9, 14, 4, 12);
    addFive(m, 9, 8, 13, 5, 15);
    addFive(m, 10, 11, 19, 7, 17);
    addFive(m, 11, 10, 16, 6, 18);

    mdls.append(m);
    m->saveTo("dodec.mdl.txt");
    return m;
}




#define COMPAR 0.001

int getPoint(Model *m, QVector3D &pnt) {
    for (int i = 0; i < m->pnts.length(); i++) {
        QVector3D &c = m->pnts[i];
        if ( (std::abs(c.x() - pnt.x()) < COMPAR) && (std::abs(c.y() - pnt.y()) < COMPAR) && (std::abs(c.z() - pnt.z()) < COMPAR) ) {
            return i;
        }
    }
    m->addPoint(pnt);
    return m->pnts.length() - 1;
}

void divideTria(Model *to, float len, QVector3D a, QVector3D b, QVector3D c, int cnt) {
    QVector3D ab = middle(a, b);
    QVector3D bc = middle(b, c);
    QVector3D ca = middle(c, a);
    float cf = len / ab.length();
    ab *= cf;
    bc *= cf;
    ca *= cf;

    if (cnt > 0) {
        cnt--;
        divideTria( to, len, ca, a, ab, cnt );
        divideTria( to, len, ab, b, bc, cnt );
        divideTria( to, len, bc, c, ca, cnt );
        divideTria( to, len, ab, bc, ca, cnt );
    } else {
        to->addTria( QRect(getPoint(to, ca), getPoint(to, a), getPoint(to, ab), -1) );
        to->addTria( QRect(getPoint(to, ab), getPoint(to, b), getPoint(to, bc), -1) );
        to->addTria( QRect(getPoint(to, bc), getPoint(to, c), getPoint(to, ca), -1) );
        to->addTria( QRect(getPoint(to, ab), getPoint(to, bc), getPoint(to, ca), -1) );
    }
}

Model* createSphere(QVector<Model*> &mdls, Model *from, int rec) {
    rec = std::max(0, std::min(2, rec));
    Model *to = new Model();
    for (int i = 0; i < from->trs.length(); i++) {
        QRect tria = from->trs[i];
        QVector3D a = from->pnts[tria.x()];
        QVector3D b = from->pnts[tria.y()];
        QVector3D c = from->pnts[tria.width()];
        // vector to the middle
        divideTria( to, a.length(), a, b, c, rec );
//        to->addTria( QRect(getPoint(to, a), getPoint(to, b), getPoint(to, c), -1) );
    }

//    qDebug() << "Points & faces of tetrah model: " << from->pnts.length() << from->trs.length();
//    qDebug() << "Points & faces of sphere model: " << to->pnts.length() << to->trs.length();

    mdls.append(to);
    to->saveTo("sphere.mdl.txt");
    return to;
}

Model* createGarlic(QVector<Model*> &mdls, Model *Sphere) {
    Model *to = new Model();
    for (int i = 0; i < Sphere->pnts.length(); i++) {
        QVector3D p = Sphere->pnts[i];
        float x = p.x();
        float y = p.y();
        float z = p.z();
        float ax = std::abs(x);
        float az = std::abs(z);
        if (y > 0) {
            y = -0.65 * y * (2 - pow(std::fmin(1 * (ax+az) / y, 1), 0.4) );
        } else {
            y /= -1.5;
        }
        z = z / (2 - pow(std::fmin(ax / (az + 0.01), 1.0), 0.25));
        x = x / (2 - pow(std::fmin(az / (ax + 0.01), 1.0), 0.25));
        to->addPoint(QVector3D( x, y, z ));
    }
    for (int i = 0; i < Sphere->trs.length(); i++) {
        to->addTria(Sphere->trs[i]);
    }

    mdls.append(to);
    to->saveTo("garlic.mdl.txt");
    return to;
}




Model* createTorus(QVector<Model*> &mdls, int counts, float ro, float ri, int turns, float addheight, float addwidth) {
    QVector<QVector3D> pointsin;
    int cntin = counts, cntout = counts, i, j;
//    float ro = 40, ri = 10;
    for (i = 0; i < cntin; i++) {
        float a = 2 * M_PI * i / cntin;
        pointsin.append(QVector3D( ri * cos(a), ri * sin(a), 0 ));
    }

    Model *res = new Model();
    int f1 = turns+1;
    cntout *= f1;

    for (i = 0; i < cntout; i++) {
        QMatrix4x4 mod1 = shift(ro + addwidth * i / cntout, addheight * (i-cntout/2) / cntout, 0) * rotateY(f1 * 360 * i / cntout);
        QMatrix4x4 mod2 = shift(ro + addwidth * (i+1) / cntout, addheight * (i+1-cntout/2) / cntout, 0) * rotateY(f1 * 360 * (i+1) / cntout);
        QVector<QVector3D> news1 = apply(pointsin, mod1);
        QVector<QVector3D> news2 = apply(pointsin, mod2);

        for (j = 0; j <= cntin; j++) {
            int c = (j+1) % cntin;
            int p = j % cntin;
            QVector3D p11 = news1[c];
            QVector3D p12 = news1[p];
            QVector3D p21 = news2[c];
            QVector3D p22 = news2[p];
            res->addTria( QRect(getPoint(res, p22), getPoint(res, p12), getPoint(res, p11), -1) );
            res->addTria( QRect(getPoint(res, p11), getPoint(res, p21), getPoint(res, p22), -1) );
        }
    }

    mdls.append(res);
//    res->saveTo("torus.mdl.txt");
    return res;
}


