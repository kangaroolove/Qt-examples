#include "Widget.h"
#include <QVBoxLayout>
#include <QLabel>

Widget::Widget(QWidget * parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* label = new QLabel("I am testApplication", this);
    layout->addWidget(label);
    this->resize(400, 300);
}

Widget::~Widget()
{

}