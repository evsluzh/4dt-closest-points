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
    core/point.cpp \
    core/route.cpp \
    routereader.cpp \
    core/simplepredictor.cpp \
    core/edge.cpp \
    core/geometrichashing.cpp \
    core/conflictpredictor.cpp \
    generatedialog.cpp \
    routesgenerator.cpp \
    routewriter.cpp \
    core/conflict.cpp \
    drawer.cpp

HEADERS += \
    core/conflictpredictor.h \
    core/geometrichashing.h \
    mainwindow.h \
    core/point.h \
    core/route.h \
    simplepredictor.h \
    routereader.h \
    core/edge.h \
    generatedialog.h \
    routesgenerator.h \
    routewriter.h \
    core/conflict.h \
    drawer.h

FORMS += \
    mainwindow.ui \
    generatedialog.ui
