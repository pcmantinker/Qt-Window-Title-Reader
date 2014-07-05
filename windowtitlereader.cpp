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
    delete m_pid;
    delete m_processName;
}
void WindowTitleReader::getWindowTitle()
{
    qDebug() << "WindowTitleReader::getWindowTitle()";
#ifdef Q_OS_WIN32
    win w;
    m_activeWindows = w.getActiveWindows();
#endif

#ifdef Q_OS_DARWIN
    Mac m;
    m_activeWindows = m.getActiveWindows();
#endif

#ifdef Q_OS_LINUX
    linux_x11 l;
    m_activeWindows = l.getActiveWindows();
#endif
    for(int i = 0; i < m_activeWindows.count(); i++)
        qDebug() << "PID: " << m_activeWindows[i].getPID() << " Process Name: " << m_activeWindows[i].getProcessName() << " Window Title: " << m_activeWindows[i].getWindowTitle();
}
