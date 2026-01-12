#include "MagnifierWidget.h"
#include <QDebug>

MagnifierWidget::MagnifierWidget(QWidget *parent)
    : QLabel(parent), m_zoomSize(QSize(300, 200)) {
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint |
                   Qt::WindowStaysOnTopHint);
    setObjectName("Magnifier");
    setStyleSheet("QLabel#Magnifier{border: 1px solid #FF0000}");
    setFixedSize(m_zoomSize);
}

QSize MagnifierWidget::getZoomSize() const { return m_zoomSize; }
