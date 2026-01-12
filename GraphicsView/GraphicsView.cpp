#include "GraphicsView.h"

#include <QCoreApplication>
#include <QDebug>
#include <QPainter>

GraphicsView::GraphicsView(QGraphicsScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent) {
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::SmoothPixmapTransform);
}

void GraphicsView::resizeEvent(QResizeEvent* event) {
    fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
    qDebug() << "scaleX = " << transform().m11();
    qDebug() << "scaleY =" << transform().m22();
    QGraphicsView::resizeEvent(event);
}

void GraphicsView::closeEvent(QCloseEvent* closeEvent) {
    QCoreApplication::quit();
}
