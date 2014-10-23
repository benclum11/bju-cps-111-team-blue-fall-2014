#-------------------------------------------------
#
# Project created by QtCreator 2014-10-23T09:41:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tile.cpp \
    world.cpp \
    building.cpp \
    unit.cpp \
    base.cpp \
    object.cpp \
    buildabletile.cpp

HEADERS  += mainwindow.h \
    tile.h \
    world.h \
    building.h \
    unit.h \
    buildabletile.h \
    base.h \
    object.h

FORMS    += mainwindow.ui
