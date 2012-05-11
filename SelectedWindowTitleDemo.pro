#-------------------------------------------------
#
# Project created by QtCreator 2012-05-09T21:19:57
#
#-------------------------------------------------

QT       += core gui

TARGET = SelectedWindowTitleDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    windowtitlereader.cpp

HEADERS  += mainwindow.h \
    windowtitlereader.h \
    mac.h

FORMS    += mainwindow.ui

macx:OBJECTIVE_SOURCES += mac.mm

macx:LIBS += -framework Cocoa
