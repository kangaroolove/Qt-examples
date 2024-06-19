#include "Widget.h"
#include <QVBoxLayout>
#include <QPushButton>

Widget::Widget(QWidget * parent)
    : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);
    auto button = new QPushButton("Quit event loop");
    layout->addWidget(button);
    connect(button, &QPushButton::clicked, this, &Widget::quitEventLoop);
    resize(400, 300);
}

Widget::~Widget()
{

}