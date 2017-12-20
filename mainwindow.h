/**
 * Copyright 2017, Barashev Ivan - All Rights Reserved.
 * Website: www.aivanf.com
 * This is proprietary software. Unauthorized commercial use of this code via any medium is strictly prohibited.
 * When use the code, you must give appropriate credit, provide a link to this license, and indicate if changes were made.
 * The work is provided "as is". You may not hold the author liable.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "viewer.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

public:
    Ui::MainWindow *ui;
    Viewer *v;
    int xdir, ydir;


protected slots:
    void todo();
    void clickInfo();
};

#endif // MAINWINDOW_H
