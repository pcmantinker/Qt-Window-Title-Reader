#include "windowtitlereader.h"

WindowTitleReader::WindowTitleReader()
{
    qDebug() << "WindowTitleReader::WindowTitleReader()";
    // refresh window reading every 10ms
    timer = new QTimer(this);
    timer->setInterval(10);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(getWindowTitle()));
}

WindowTitleReader::~WindowTitleReader()
{
    delete timer;
}
void WindowTitleReader::getWindowTitle()
{
    qDebug() << "WindowTitleReader::getWindowTitle()";
#ifdef Q_WS_WIN
    GetWindowText(GetForegroundWindow(), buf, 255);
#ifdef UNICODE
    qstrMessage = QString::fromUtf16((ushort*)buf);
#else
    qstrMessage = QString::fromLocal8Bit(buf);
#endif
    qDebug() << qstrMessage;
#endif

#ifdef Q_WS_MACX
    Mac m;
    m.getWindowTitle();
#endif

#ifdef Q_WS_X11
    linux_x11 l;
    Display *display = XOpenDisplay (NULL);
    int screen = DefaultScreen (display);

//    //XSetErrorHandler(ErrorHandler);

    Window rootWindow = RootWindow (display, screen);
    l.enumerateWindows(display, rootWindow);
    XCloseDisplay (display);
#endif
}
