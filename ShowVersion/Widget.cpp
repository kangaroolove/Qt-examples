#include "VersionConfig.h"
#include "Widget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QString>
#include <iostream>

Widget::Widget(QWidget * parent)
    : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);
    auto label = new QLabel;
    label->setText(QString("Version: %1.%2.%3").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_PATCH));
    layout->addWidget(label);
    this->resize(400, 300);
}

Widget::~Widget()
{

}