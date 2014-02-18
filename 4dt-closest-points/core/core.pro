INCLUDEPATH += . ..

TEMPLATE = lib

CONFIG += staticlib

QMAKE_CXXFLAGS += -std=c++0x

HEADERS += \
    conflictpredictor.h \
    geometrichashing.h \
    point.h \
    route.h \
    simplepredictor.h \
    edge.h \
    conflict.h

SOURCES += \
    point.cpp \
    route.cpp \
    simplepredictor.cpp \
    edge.cpp \
    geometrichashing.cpp \
    conflictpredictor.cpp \
    conflict.cpp
