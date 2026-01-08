#include "GraphicsView.h"

#include <QPainter>

GraphicsView::GraphicsView(QGraphicsScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent) {
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::SmoothPixmapTransform);
}

void GraphicsView::resizeEvent(QResizeEvent* event) {
    fitInView(scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
    QGraphicsView::resizeEvent(event);
}
