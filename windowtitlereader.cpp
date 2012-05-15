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
    unsigned long len;
    Display *disp = XOpenDisplay(NULL);
    Window *list;
    char *name;
    char* command;

    list = (Window*)l.active(disp,&len);
    for (int i=0;i<(int)len;i++) {
        name = l.name(disp,list[i]);
        command = l.command(disp, list[i]);
        qDebug() << i << " : " << name;
        if(command)
            qDebug() << "Command : " << command;
        delete name;
        delete command;
    }
    delete list;
    XCloseDisplay (disp);
#endif
}
