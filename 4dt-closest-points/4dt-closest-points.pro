#-------------------------------------------------
#
# Project created by QtCreator 2013-11-07T20:20:13
#
#-------------------------------------------------

#QT       += core

QMAKE_CXXFLAGS += -std=c++0x

TEMPLATE = subdirs

SUBDIRS += \
        core \
        gui \
        build

gui.depends = core
build.depends = gui
