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
    win w;
    w.getWindowTitle();
#endif

#ifdef Q_WS_MACX
    Mac m;
    m.getWindowTitle();
#endif

#ifdef Q_WS_X11
    linux_x11 l;
    l.getWindowTitle();
#endif
}
