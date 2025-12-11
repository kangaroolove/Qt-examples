#include "Widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    resize(800, 600);
    setObjectName("Widget");
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("QWidget#Widget{background-color:red;}");
}