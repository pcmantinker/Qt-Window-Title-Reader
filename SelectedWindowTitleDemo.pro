#-------------------------------------------------
#
# Project created by QtCreator 2012-05-09T21:19:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WindowInfo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    windowtitlereader.cpp \
    windowinfo.cpp


HEADERS  += mainwindow.h \
    windowtitlereader.h \
    windowinfo.h

macx {
    OBJECTIVE_SOURCES += mac.mm
    HEADERS += mac.h
    LIBS += -framework Cocoa
}

unix:!macx {
    HEADERS += linux_x11.h
    SOURCES += linux_x11.cpp
    LIBS += -lX11
}

win32 {
    SOURCES += win.cpp
    HEADERS += win.h
    LIBS += -lpsapi
}
