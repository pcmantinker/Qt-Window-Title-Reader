#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "windowtitlereader.h"

class MainWindow : public QWidget
{
    Q_OBJECT
    
public:
    MainWindow();
    ~MainWindow();
    
private:
    QString qstrMessage;
    WindowTitleReader* wtr;
};

#endif // MAINWINDOW_H
