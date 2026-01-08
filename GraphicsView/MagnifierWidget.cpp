#include "MagnifierWidget.h"
#include <QDebug>

MagnifierWidget::MagnifierWidget(QWidget *parent) : QLabel(parent) {
    setAttribute(Qt::WA_StyledBackground);
    // setObjectName("Widget");
    // setStyleSheet("QWidget#Widget{border: 1px solid #FF0000}");
    resize(200, 100);
}