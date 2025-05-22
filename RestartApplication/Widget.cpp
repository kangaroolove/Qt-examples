#include "Widget.h"
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QProcess>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    auto layout = new QVBoxLayout(this);
    QPushButton *restartButton = new QPushButton("Restart", this);
    connect(restartButton, &QPushButton::clicked, this, [this] {
        QApplication::quit();
        qDebug() << QProcess::startDetached(QApplication::applicationFilePath(),
                                            QStringList());
    });
    layout->addWidget(restartButton);

    this->resize(400, 300);
}

Widget::~Widget() { qDebug() << "~Widget"; }