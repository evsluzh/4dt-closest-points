QMAKE_CXXFLAGS += -std=c++0x

TEMPLATE = lib

SOURCES += \
    point.cpp \
    route.cpp \
    simplepredictor.cpp \
    edge.cpp \
    geometrichashing.cpp \
    conflictpredictor.cpp \
    conflict.cpp

HEADERS += \
    conflictpredictor.h \
    geometrichashing.h \
    point.h \
    route.h \
    edge.h \
    conflict.h
