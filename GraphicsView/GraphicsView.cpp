#include "GraphicsView.h"

#include <QCoreApplication>
#include <QDebug>
#include <QPainter>

GraphicsView::GraphicsView(QGraphicsScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent), m_fitInViewScale(1) {
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::SmoothPixmapTransform);
}

void GraphicsView::resizeEvent(QResizeEvent* event) {
    fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
    auto fitInViewScale = transform().m11();
    if (m_fitInViewScale != fitInViewScale) {
        m_fitInViewScale = fitInViewScale;
        emit fitInViewScaleChanged(fitInViewScale);
    }
    QGraphicsView::resizeEvent(event);
}

void GraphicsView::closeEvent(QCloseEvent* closeEvent) {
    QCoreApplication::quit();
}
