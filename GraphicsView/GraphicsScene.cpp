#include "GraphicsScene.h"

#include <QDebug>
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

GraphicsScene::GraphicsScene(QObject* parent)
    : QGraphicsScene(parent),
      m_magnifierWidget(std::make_unique<MagnifierWidget>()) {
    QPixmap pixmap("D:/2.jpg");
    auto pixmapItem = addPixmap(pixmap);
    pixmapItem->setTransformationMode(Qt::SmoothTransformation);

    addText("Hello, world");

    auto text2 = addText("Second Text");
    text2->setPos(50, 50);

    m_magnifierWidget->move(0, 0);
    m_magnifierWidget->show();
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    // // if ((pos.x() >= 200 / 2 || pos.x() <= 1280 - (200 / 2)) &&
    // //         pos.y() >= 100 / 2 ||
    // //     pos.y() <= 720 - (100 / 2))
    // m_magnifierProxyWidget->setPos(pos.x() - (200 / 2), pos.y() - (100 / 2));

    auto width = m_magnifierWidget->width();
    auto height = m_magnifierWidget->height();

    auto scenePos = mouseEvent->scenePos();
    QRectF rect(scenePos.x() - (width / 2), scenePos.y() - (height / 2), width,
                height);

    QImage image(width, height, QImage::Format_ARGB32);
    image.fill(Qt::transparent);  // clear the background

    // 3. Initialize a QPainter on the image
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    render(&painter, image.rect(), rect);
    painter.end();

    auto screenPos = mouseEvent->screenPos();
    m_magnifierWidget->move(screenPos);

    m_magnifierWidget->setPixmap(QPixmap::fromImage(image));

    QGraphicsScene::mouseMoveEvent(mouseEvent);
}
