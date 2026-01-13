#include "MagnifierWidget.h"

#include <QDebug>
#include <QMouseEvent>

MagnifierWidget::MagnifierWidget(QWidget *parent)
    : QLabel(parent), m_zoomSize(QSize(300, 200)), m_zoomFactor(1) {
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint |
                   Qt::WindowStaysOnTopHint);
    setObjectName("Magnifier");
    setStyleSheet("QLabel#Magnifier{border: 1px solid #FF0000}");
    setFixedSize(m_zoomSize);
    setMouseTracking(true);
}

QSize MagnifierWidget::getZoomSize() const { return m_zoomSize; }
