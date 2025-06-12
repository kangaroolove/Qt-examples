#include "Widget.h"
#include "SimpleTask.h"
#include <QThreadPool>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    for (int i = 0; i < 20; ++i)
        QThreadPool::globalInstance()->start(new SimpleTask(i));
}

Widget::~Widget() {}