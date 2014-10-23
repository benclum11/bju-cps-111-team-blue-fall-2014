#-------------------------------------------------
#
# Project created by QtCreator 2014-10-23T09:41:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++0x

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
    highscore.cpp \
    load.cpp \
    save.cpp

HEADERS  += mainwindow.h \
    tile.h \
    world.h \
    building.h \
    unit.h \
    base.h \
    object.h \
    highscore.h \
    load.h \
    save.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

