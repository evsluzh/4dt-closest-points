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

TEMPLATE = subdirs

SUBDIRS += core

SOURCES += main.cpp \
    mainwindow.cpp \
    routereader.cpp \
    generatedialog.cpp \
    routesgenerator.cpp \
    routewriter.cpp \
    drawer.cpp

HEADERS += \
    mainwindow.h \
    simplepredictor.h \
    routereader.h \
    generatedialog.h \
    routesgenerator.h \
    routewriter.h \
    drawer.h

FORMS += \
    mainwindow.ui \
    generatedialog.ui

OTHER_FILES += \
    core/core.pro
