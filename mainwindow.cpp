/**
 * Copyright 2017, Barashev Ivan - All Rights Reserved.
 * Website: www.aivanf.com
 * This is proprietary software. Unauthorized commercial use of this code via any medium is strictly prohibited.
 * When use the code, you must give appropriate credit, provide a link to this license, and indicate if changes were made.
 * The work is provided "as is". You may not hold the author liable.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QMessageBox>
#include <QPainter>
#include <QtMath>
#include <QKeyEvent>

#include "helper.h"
#include "data.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);

    v = new Viewer(width(), height());
    xdir = 20;
    ydir = 10;

    // Axes
//    Model *m = new Model();
//    float phi = (1 + sqrt(5)) / 2;
//    float b = 20 / phi;
//    float a = 20;
//    m->addPoint(QVector3D(0, 0, 0));
//    m->addPoint(QVector3D(500, 0, 0));
//    m->addPoint(QVector3D(0, 500, 0));
//    m->addPoint(QVector3D(0, 0, 500));
//    m->addTria( QRect(0, 1, 0, -1) );
//    m->addTria( QRect(0, 2, 0, -1) );
//    m->addTria( QRect(0, 3, 0, -1) );
//    v->items.append(new Item(m));

//    Model *isoc = createIcosahedron(v->mdls);
    Model *isoc = new Model();
    isoc->loadFrom("isoc.mdl.txt");

//    Model *dodec = createDodecahedron(v->mdls);
    Model *dodec = new Model();
    dodec->loadFrom("dodec.mdl.txt");

//    Model *octa = createOctahedron(v->mdls);
    Model *octa = new Model();
    octa->loadFrom("octa.mdl.txt");

//    Model *tetra = createTetrahedron(v->mdls);
    Model *tetra = new Model();
    tetra->loadFrom("tetra.mdl.txt");

//    Model *box = createHexahedron(v->mdls);
    Model *box = new Model();
    box->loadFrom("box.mdl.txt");

    Model *sphere = createSphere(v->mdls, isoc, 1);
//    Model *sphere = new Model();
//    sphere->loadFrom("sphere.mdl.txt");


    Model *torus = createTorus(v->mdls, 18, 20, 10, 0, 0, 0);
    Model *spring = createTorus(v->mdls, 6, 12, 4, 2, 60, 0);
    Model *spiral = createTorus(v->mdls, 6, 16, 4, 1, 0, 30);
    Model *combi = createTorus(v->mdls, 8, 18, 6, 2, 80, 40);
    Model *garlic = createGarlic(v->mdls, sphere);


//    v->items.append(new Item(isoc, -120, 0, 0));
//    v->items.append(new Item(tetra, 120, 0, 0));
//    v->items.append(new Item(dodec, 0, -120, 0));
//    v->items.append(new Item(box, 0, 120, 0));
//    v->items.append(new Item(sphere, 0, 0, -120));
//    v->items.append(new Item(octa, 0, 0, 120));

    v->items.append(new Item(combi, 0, -120, -120));
    v->items.append(new Item(torus, -120, -120, 0));
    v->items.append(new Item(spring, 120, 120, 0));
    v->items.append(new Item(spiral, -120, 0, -120));
    v->items.append(new Item(garlic, 0, 120, 120));

//    v->items.append(new Item(isoc, 0, 1000, 0));
//    v->items.append(new Item(tetra, 0, -1000, 0));
//    v->items.append(new Item(box, 1000, 0, 0));
//    v->items.append(new Item(sphere, -1000, 0, 0));
//    v->items.append(new Item(octa, 0, 0, -1000));
//    v->items.append(new Item(dodec, 0, 1000, 0));

    QObject::connect(ui->btnInfo, SIGNAL(clicked(bool)), this, SLOT(clickInfo()));

//    QTimer *timer = new QTimer(this);
//    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(todo()));
//    timer->start(60);
//    timer->start(1000);
    QTimer::singleShot(100, this, SLOT(todo()));
}

MainWindow::~MainWindow() {
    delete ui;
    delete v;
}

void MainWindow::todo() {
    v->useRoberts = ui->ch_rob->isChecked();
    v->usePerspective = ui->ch_persp->isChecked();
    v->useZbuffer = ui->ch_zbuf->isChecked();
    v->rx = (v->rx + xdir);
    v->ry = (v->ry + ydir);
    v->rx = gradus(v->rx);
    v->ry = gradus(v->ry);
    int msec = v->process();
    QString pr = "";
    if (v->filling == 0) {
        pr += "Filling: edges\n";
    } else if (v->filling == 1) {
        pr += "Filling: Goraund\n";
    } else if (v->filling == 2) {
        pr += "Filling: Phong\n";
    }
    pr += "Scale: " + QString::number(v->sc) + "\n";
    pr += "Rotation X: " + QString::number(v->rx) + "°, Rotation Y: " + QString::number(v->ry) + "°" + "\n";
    pr += "Intensity: " + QString::number(v->intensity) + "/10 ambient: " + QString::number(v->ambient) + " power: " + QString::number(v->power) + "\n";
    pr += "Milliseconds: " + QString::number(msec);
    ui->label->setText(pr);
    update();
    QTimer::singleShot(200 + (1 - v->useZbuffer) * 300, this, SLOT(todo()));
}

void MainWindow::clickInfo() {
    QMessageBox msgBox;
    msgBox.setText("Homework for Computer graphics 15.11.2017. Made by Barashev Iven SE141.\n\n"
                   "Content: 3D engine, Roberts algorithm, shading filling, Platonic solids, sphere, Torus and its modifications.\n\n"
                   "Control:\nArrows - rotating;\nZ/X - scaling;\n"
                   "Q/W/E/R/T/Y - changing light intensity, degree of ambient light and exponent for reflected light;\n"
                   "A/S/D - edges, Goraund and Phong filling.");
    msgBox.exec();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_A) {
        v->filling = 0;
    } else if (event->key() == Qt::Key_S) {
        v->filling = 1;
    } else if (event->key() == Qt::Key_D) {
        v->filling = 2;
    }
    if (event->key() == Qt::Key_Space) {
        xdir = 0;
        ydir = 0;
    }
    if (event->key() == Qt::Key_Down) {
        if (xdir > -20) {
            xdir -= 5;
        }
    } else if (event->key() == Qt::Key_Up) {
        if (xdir < 20) {
            xdir += 5;
        }
    }
    if (event->key() == Qt::Key_Right) {
        if (ydir > -20) {
            ydir -= 5;
        }
    } else if (event->key() == Qt::Key_Left) {
        if (ydir < 10) {
            ydir += 5;
        }
    }
    if (event->key() == Qt::Key_Z) {
        if (v->sc > 0.3) {
            v->sc -= 0.2;
        }
    } else if (event->key() == Qt::Key_X) {
        if (v->sc < 4) {
            v->sc += 0.2;
        }
    }
    if (event->key() == Qt::Key_Q) {
        if (v->intensity < 10) {
            v->intensity += 1;
        }
    } else if (event->key() == Qt::Key_W) {
        if (v->intensity > 1) {
            v->intensity -= 1;
        }
    }
    if (event->key() == Qt::Key_E) {
        if (v->ambient <= 0.9) {
            v->ambient += 0.1;
        }
    } else if (event->key() == Qt::Key_R) {
        if (v->ambient > 0) {
            v->ambient -= 0.1;
        }
    }
    if (event->key() == Qt::Key_T) {
        if (v->power <= 14) {
            v->power += 2;
        }
    } else if (event->key() == Qt::Key_Y) {
        if (v->power > 2) {
            v->power -= 2;
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *event) {
    (void)event;
    QPainter pntr(this);
    pntr.setPen(QColor(0, 0, 0));
    if (v->useZbuffer) {
        pntr.drawPixmap(0, 0, width(), height(), v->image2);
    } else {
        pntr.drawPixmap(0, 0, width(), height(), v->image1);
    }
}
