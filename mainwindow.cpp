#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow()
{
    wtr = new WindowTitleReader();
    this->setWindowTitle("Selected Window Title Demo");
}

MainWindow::~MainWindow()
{

}


