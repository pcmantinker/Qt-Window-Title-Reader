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
    windowtitlereader.cpp \
    linux_x11.cpp

HEADERS  += mainwindow.h \
    windowtitlereader.h \
    mac.h \
    linux_x11.h

FORMS    += mainwindow.ui

macx:OBJECTIVE_SOURCES += mac.mm

macx:LIBS += -framework Cocoa


unix:LIBS += -lX11
