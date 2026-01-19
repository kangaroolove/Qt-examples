#include "MagnifierWidget.h"

#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>

MagnifierWidget::MagnifierWidget(QWidget *parent)
    : QLabel(parent),
      m_viewportSize(QSize(300, 200)),
      m_zoomFactor(1.0),
      m_enableMove(true) {
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint |
                   Qt::WindowStaysOnTopHint);
    setObjectName("Magnifier");
    setStyleSheet("QLabel#Magnifier{border: 1px solid #FF0000}");
    setFixedSize(m_viewportSize);
    setMouseTracking(true);
}

QSize MagnifierWidget::getViewportSize() const { return m_viewportSize; }

QSize MagnifierWidget::getZoomSize() const {
    return QSize(m_viewportSize.width() / m_zoomFactor,
                 m_viewportSize.height() / m_zoomFactor);
}

void MagnifierWidget::setZoomFactor(const double &factor) {
    if (factor == 0) return;

    m_zoomFactor = factor;
}

void MagnifierWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_C)
        m_enableMove = false;
    else if (event->key() == Qt::Key_V)
        m_enableMove = true;
    QLabel::keyPressEvent(event);
}
