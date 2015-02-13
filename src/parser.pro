TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../bin

TARGET = parser

SOURCES += main.cpp \
    fileparser.cpp \
    medianholder.cpp \
    filewriter.cpp \
    md5.cpp \
    utils.cpp


DISTFILES += \
    readme.txt \
    data_gen.py

HEADERS += \
    fileparser.h \
    medianholder.h \
    filewriter.h \
    md5.h \
    utils.h

