#-------------------------------------------------
#
# Project created by QtCreator 2016-06-18T09:32:36
#
#-------------------------------------------------

QT       += testlib
QT       -= gui

TARGET = tst_flowchart
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

CONFIG(debug, debug|release) {
    DESTDIR = debug
} else {
    DESTDIR = release
}

INCLUDEPATH += ../compiler
LIBS += -static -L$$shell_quote($$shell_path($$OUT_PWD/../compiler/$$DESTDIR)) -lcompiler

SOURCES += tst_flowchart.cpp \
    tst_flowchart.cpp
