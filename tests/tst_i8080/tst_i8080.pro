QT += core testlib

TARGET = tst_i8080

CONFIG += qt warn_on depend_includepath testcase console
CONFIG += c++11
DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += $$PWD/../microsha
DEPENDPATH += $$PWD/../microsha

TEMPLATE = app
HEADERS += \
         $$PWD/../../microsha/i8080.h
SOURCES += \
           Test_i8080.cpp \
         $$PWD/../../microsha/i8080.cpp

