#-------------------------------------------------
#
# Project created by QtCreator 2021-11-09T19:57:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testplugin
TEMPLATE = app

LIBS += $$PWD/lib/qmyextlabelplugin.lib
INCLUDEPATH += $$PWD/include


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui
