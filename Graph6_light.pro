#-------------------------------------------------
#
# Project created by QtCreator 2017-11-11T16:28:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Graph6_light
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    data.cpp \
    item.cpp \
    model.cpp \
    helper.cpp \
    viewer.cpp

HEADERS  += mainwindow.h \
    data.h \
    item.h \
    model.h \
    helper.h \
    viewer.h

FORMS    += mainwindow.ui
