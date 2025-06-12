#include "MainWindow.h"
#include <QDebug>
#include <QGuiApplication>
#include <QLabel>
#include <QList>
#include <QScreen>

MainWindow::MainWindow() {
    auto label = new QLabel("Main window", this);
    connect(qApp, &QGuiApplication::screenAdded, this,
            &MainWindow::screenAdded);
    connect(qApp, &QGuiApplication::screenRemoved, this, [this] {
        qDebug() << "screen removed";
        printGeometry();
    });

    this->setObjectName("MainWinodow");
    this->setStyleSheet("QMainWindow#MainWinodow{background-color:red;}");

    printGeometry();
}

MainWindow::~MainWindow() {}

void MainWindow::showEvent(QShowEvent *event) {
    qDebug() << "save main geometry";
    m_rect = geometry();
    qDebug() << "main rect = " << m_rect;
}

void MainWindow::printGeometry() {
    auto screens = QGuiApplication::screens();
    for (int i = 0; i < screens.size(); ++i)
        qDebug() << "screen " << i << " name" << screens[i]->name()
                 << " geometry = " << screens[i]->geometry();
}

void MainWindow::screenAdded(QScreen *screen) {
    qDebug() << "Screen Added";

    qDebug() << "MainWindow size = " << this->size();

    printGeometry();
    auto screens = QGuiApplication::screens();
    if (screens.size() == 2) {
        qDebug() << "restore main geometry";
        setGeometry(screen->geometry());
    }
}