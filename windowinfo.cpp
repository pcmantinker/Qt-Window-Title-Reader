#include "windowinfo.h"

WindowInfo::WindowInfo()
{
}

QString WindowInfo::getWindowTitle()
{
    return this->m_windowTitle;
}

long WindowInfo::getPID()
{
    return this->m_pid;
}

QString WindowInfo::getProcessName()
{
    return this->m_processName;
}

void WindowInfo::setWindowTitle(QString windowTitle)
{
    m_windowTitle = windowTitle;
}

void WindowInfo::setPID(long pid)
{
    m_pid = pid;
}

void WindowInfo::setProcessName(QString processName)
{
    m_processName = processName;
}
