#include "MagnifierWidget.h"
#include <QDebug>

MagnifierWidget::MagnifierWidget(QWidget *parent) : QLabel(parent) {
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint |
                   Qt::WindowStaysOnTopHint);
    setObjectName("Magnifier");
    setStyleSheet("QLabel#Magnifier{border: 1px solid #FF0000}");
    resize(200, 100);
}