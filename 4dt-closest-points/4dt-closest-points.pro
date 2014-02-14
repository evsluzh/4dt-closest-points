#-------------------------------------------------
#
# Project created by QtCreator 2013-11-07T20:20:13
#
#-------------------------------------------------

#QT       += core

QT       += gui

QT       += Widgets

QMAKE_CXXFLAGS += -std=c++0x

TARGET = 4dt-closest-points
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp \
    point.cpp \
    route.cpp \
    routereader.cpp \
    simplepredictor.cpp \
    edge.cpp \
    geometrichashing.cpp \
    conflictpredictor.cpp \
    generatedialog.cpp \
    routesgenerator.cpp \
    routewriter.cpp \
    conflict.cpp \
    drawer.cpp

HEADERS += \
    conflictpredictor.h \
    geometrichashing.h \
    mainwindow.h \
    point.h \
    route.h \
    simplepredictor.h \
    routereader.h \
    edge.h \
    generatedialog.h \
    routesgenerator.h \
    routewriter.h \
    conflict.h \
    drawer.h

FORMS += \
    mainwindow.ui \
    generatedialog.ui
