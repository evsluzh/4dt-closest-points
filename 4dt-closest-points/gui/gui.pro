QT += core widgets

TEMPLATE = lib

CONFIG += staticlib

LIBS += -L../core -lcore

INCLUDEPATH += . ..

QMAKE_CXXFLAGS += -std=c++0x

HEADERS += \
    drawer.h \
    mainwindow.h \
    generatedialog.h \
    drawer.h \
    routereader.h \
    routewriter.h \
    routesgenerator.h

SOURCES += drawer.cpp \
    mainwindow.cpp \
    generatedialog.cpp \
    drawer.cpp \
    routereader.cpp \
    routewriter.cpp \
    routesgenerator.cpp

FORMS += \
    mainwindow.ui \
    generatedialog.ui
