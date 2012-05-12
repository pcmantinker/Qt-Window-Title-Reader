#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow()
{
    qDebug() << "MainWindow::MainWindow()";
    wtr = new WindowTitleReader();
    this->setWindowTitle("Selected Window Title Demo");
}

MainWindow::~MainWindow()
{

}

void MainWindow::getWindowTitle()
{
    qDebug() << "Test";
}


