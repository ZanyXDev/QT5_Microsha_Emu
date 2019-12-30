QT += core testlib

TARGET = tst_i8080

CONFIG += qt warn_on depend_includepath testcase console
CONFIG   -= app_bundle

DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += $$PWD/../Microsha
DEPENDPATH += $$PWD/../Microsha

TEMPLATE = app


HEADERS += \
         ../../microsha/simple.h

SOURCES +=  \
         Test_i8255.cpp \
         ../../microsha/simple.cpp

