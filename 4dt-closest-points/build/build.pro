QT += core widgets

QMAKE_CXXFLAGS += -std=c++0x

TEMPLATE = app

TARGET = ../4dt-closest-points

INCLUDEPATH += . ..

LIBS += ../gui/libgui.a ../core/libcore.a

SOURCES += \
        main.cpp

