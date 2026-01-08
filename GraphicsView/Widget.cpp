#include "Widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    setAttribute(Qt::WA_StyledBackground);
    setObjectName("Widget");
    setStyleSheet("QWidget#Widget{border: 1px solid #FF0000}");
}