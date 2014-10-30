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
    buildablelabel.cpp \
    helpwindow.cpp \
    gamelobby.cpp \
    titlewindow.cpp \
    gamewindow.cpp \
    stats.cpp \
    displaybuilding.cpp

HEADERS  += \
    buildablelabel.h \
    helpwindow.h \
    gamelobby.h \
    titlewindow.h \
    gamewindow.h \
    stats.h \
    displaybuilding.h

FORMS    += \
    helpwindow.ui \
    gamelobby.ui \
    titlewindow.ui \
    gamewindow.ui

RESOURCES += \
    client-resources.qrc
