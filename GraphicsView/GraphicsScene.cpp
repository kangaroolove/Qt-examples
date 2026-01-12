#include "GraphicsScene.h"

#include <QDebug>
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QPainter>

GraphicsScene::GraphicsScene(QObject* parent)
    : QGraphicsScene(parent),
      m_magnifierWidget(std::make_unique<MagnifierWidget>()),
      m_fitInViewScale(1) {
    QPixmap pixmap("D:/2.jpg");
    auto pixmapItem = addPixmap(pixmap);
    pixmapItem->setTransformationMode(Qt::SmoothTransformation);

    addText("Hello, world");

    auto text2 = addText("Second Text");
    text2->setPos(40, 40);

    m_magnifierWidget->move(0, 0);
    m_magnifierWidget->show();
    m_magnifierWidget->installEventFilter(this);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    auto scenePos = mouseEvent->scenePos();
    moveMagnifierWidget(mouseEvent->screenPos());
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void GraphicsScene::keyPressEvent(QKeyEvent* keyEvent) {
    if (keyEvent->key() == Qt::Key_M) {
        auto width = m_magnifierWidget->getZoomSize().width();
        auto height = m_magnifierWidget->getZoomSize().height();

        QRect rect(40, 40, width, height);
        addRect(rect, QColor(255, 0, 0));
    } else if (keyEvent->key() == Qt::Key_N) {
        auto width = m_magnifierWidget->getZoomSize().width();
        auto height = m_magnifierWidget->getZoomSize().height();

        auto scale = 0.797765;

        m_magnifierWidget->setFixedSize(width * scale, height * scale);
    } else if (keyEvent->key() == Qt::Key_B) {
        auto scale = 0.797765;

        auto width = m_magnifierWidget->getZoomSize().width();
        auto height = m_magnifierWidget->getZoomSize().height();

        QRectF rect(40, 40, width, height);

        QImage image(width * scale, height * scale, QImage::Format_ARGB32);
        image.fill(Qt::transparent);  // clear the background

        // 3. Initialize a QPainter on the image
        QPainter painter(&image);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);

        render(&painter, image.rect(), rect);
        painter.end();

        qDebug() << image.rect();

        m_magnifierWidget->setPixmap(QPixmap::fromImage(image));
    }
    QGraphicsScene::keyPressEvent(keyEvent);
}

bool GraphicsScene::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::MouseMove) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (!views().isEmpty()) {
            auto view = views().first();
            auto viewPos = view->mapFromGlobal(mouseEvent->globalPos());
            auto scenePos = view->mapToScene(viewPos);
            // qDebug() << "scenePos = " << scenePos;
            updateMagnifierDisplayPicture(scenePos);
        }
        moveMagnifierWidget(mouseEvent->globalPos());
    }

    return QGraphicsScene::eventFilter(obj, event);
}

void GraphicsScene::onFitInViewScaleChanged(double scale) {
    m_fitInViewScale = scale;
    updateMagnifierWidgetSize(scale);
}

void GraphicsScene::moveMagnifierWidget(const QPoint& screenPos) {
    auto newX = screenPos.x() - (m_magnifierWidget->width() / 2);
    auto newY = screenPos.y() - (m_magnifierWidget->height() / 2);
    m_magnifierWidget->move(newX, newY);
}

void GraphicsScene::updateMagnifierDisplayPicture(const QPointF& scenePos) {
    auto width = m_magnifierWidget->getZoomSize().width();
    auto height = m_magnifierWidget->getZoomSize().height();

    QRectF rect(scenePos.x() - (width / 2), scenePos.y() - (height / 2), width,
                height);

    QImage image(width * m_fitInViewScale, height * m_fitInViewScale,
                 QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    render(&painter, image.rect(), rect);
    painter.end();

    m_magnifierWidget->setPixmap(QPixmap::fromImage(image));
}

void GraphicsScene::updateMagnifierWidgetSize(const double& fitInViewScale) {
    auto width = m_magnifierWidget->getZoomSize().width();
    auto height = m_magnifierWidget->getZoomSize().height();
    m_magnifierWidget->setFixedSize(width * fitInViewScale,
                                    height * fitInViewScale);
}
