#include "windowtitlereader.h"

WindowTitleReader::WindowTitleReader()
{
    qDebug() << "WindowTitleReader::WindowTitleReader()";
    timer = new QTimer(this);
    timer->setInterval(10);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(getWindowTitle()));
}

WindowTitleReader::~WindowTitleReader()
{
    delete timer;
}

void WindowTitleReader::init()
{
    qDebug() << "WindowTitleReader::init()";
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
}
