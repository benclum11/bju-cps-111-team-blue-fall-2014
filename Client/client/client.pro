#-------------------------------------------------
#
# Project created by QtCreator 2014-10-23T09:41:08
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
        mainwindow.cpp \
    buildablelabel.cpp

HEADERS  += mainwindow.h \
    buildablelabel.h

FORMS    += mainwindow.ui

RESOURCES += \
    client-resources.qrc
