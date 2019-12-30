QT += core testlib

TARGET = tst_i8080

CONFIG += qt warn_on depend_includepath testcase console

DEFINES += SRCDIR=\\\"$$PWD/\\\"6

INCLUDEPATH += $$PWD/../microsha
DEPENDPATH += $$PWD/../microsha

TEMPLATE = app
HEADERS += \
         $$PWD/../../microsha/simple.h
SOURCES += \
           Test_i8080.cpp \
         $$PWD/../../microsha/simple.cpp

