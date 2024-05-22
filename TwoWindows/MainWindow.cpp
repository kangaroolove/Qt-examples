#include "MainWindow.h"
#include <QLabel>
#include <QGuiApplication>
#include <QScreen>
#include <QDebug>

MainWindow::MainWindow()
{
    auto label = new QLabel("Main window", this);
    connect(qApp, &QGuiApplication::screenAdded, this, &MainWindow::screenAdded);
}

MainWindow::~MainWindow()
{

}

void MainWindow::showEvent(QShowEvent *event)
{
    qDebug()<<"save main geometry";
    m_rect = geometry();
    qDebug()<<"main rect = "<<m_rect;
}

void MainWindow::screenAdded(QScreen *screen)
{
    auto screens = QGuiApplication::screens();
    if (screens.size() == 2)
    {
        qDebug()<<"restore main geometry";
        setGeometry(m_rect);
        showFullScreen();
    }
}