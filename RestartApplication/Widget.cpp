#include "Widget.h"
#include <QProcess>
#include <QPushButton>
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTimer>

Widget::Widget(QWidget * parent)
    : QWidget(parent)
{
    QPushButton* restartButton = new QPushButton("Restart", this);
    connect(restartButton, &QPushButton::clicked, this, [this]{
        QApplication::quit();
        qDebug()<<QProcess::startDetached(QApplication::applicationFilePath(), QStringList());
    });

    this->resize(400, 300);
}

Widget::~Widget()
{
    qDebug()<<"~Widget";
}