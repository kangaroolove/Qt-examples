#include "Widget.h"

Widget::Widget(QWidget * parent)
    : QWidget(parent)
{
    init();
}

Widget::~Widget()
{

}

void Widget::init()
{
    int *p = new int[10];
}
