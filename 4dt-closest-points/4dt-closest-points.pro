#-------------------------------------------------
#
# Project created by QtCreator 2013-11-07T20:20:13
#
#-------------------------------------------------

#QT       += core

QT       += gui

QMAKE_CXXFLAGS += -std=c++0x

TARGET = 4dt-closest-points
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp \
    Point.cpp \
    Route.cpp \
    SimplePredictor.cpp

HEADERS += \
    Point.h \
    Route.h \
    GeometricHashing.h \
    ConflictPredictor.h \
    mainwindow.h \
    RouteReader.h \
    SimplePredictor.h

FORMS += \
    mainwindow.ui
