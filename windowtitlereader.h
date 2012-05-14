#ifndef WINDOWTITLEREADER_H
#define WINDOWTITLEREADER_H
#include <QtCore>
#ifdef Q_WS_WIN
#include "qt_windows.h"
#endif

#ifdef Q_WS_MACX
#include "mac.h"
#endif

#ifdef Q_WS_X11
#include "linux_x11.h"
#endif

class WindowTitleReader : public QObject
{
    Q_OBJECT
public:
    WindowTitleReader();
    ~WindowTitleReader();
    QString qstrMessage;

private:
#ifdef Q_WS_WIN
    TCHAR buf[255];
#endif
    QTimer* timer;

private slots:
    void getWindowTitle();
};

#endif // WINDOWTITLEREADER_H
