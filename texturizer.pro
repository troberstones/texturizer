#-------------------------------------------------
#
# Project created by QtCreator 2013-11-11T22:35:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = texturizer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tile.cpp \
    canvas.cpp \
    renderer.cpp \
    tilemanager.cpp \
    atest.cpp \
    tilemgrdatamodel.cpp \
    tiledatamodel.cpp

HEADERS  += mainwindow.h \
    tile.h \
    canvas.h \
    renderer.h \
    tilemanager.h \
    atest.h \
    tilemgrdatamodel.h \
    tiledatamodel.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    GamePlan.txt
