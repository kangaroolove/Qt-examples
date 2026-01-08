#include "GraphicsScene.h"

#include <QDebug>
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneMouseEvent>
#include <QLabel>
#include <QPainter>

#include "Widget.h"

GraphicsScene::GraphicsScene(QObject* parent) : QGraphicsScene(parent) {
    QPixmap pixmap("D:/2.jpg");
    auto pixmapItem = addPixmap(pixmap);
    pixmapItem->setTransformationMode(Qt::SmoothTransformation);

    addText("Hello, world");

    auto text2 = addText("Second Text");
    text2->setPos(50, 50);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    // This one always return 0
    // qDebug() << "mouseEvent->pos = " << mouseEvent->pos();
    auto pos = mouseEvent->scenePos();
    qDebug() << "mouseEvent->scenePos" << pos;

    // m_magnifierProxyWidget->setVisible(false);

    // // if ((pos.x() >= 200 / 2 || pos.x() <= 1280 - (200 / 2)) &&
    // //         pos.y() >= 100 / 2 ||
    // //     pos.y() <= 720 - (100 / 2))
    // m_magnifierProxyWidget->setPos(pos.x() - (200 / 2), pos.y() - (100 / 2));

    // QRect rect(std::round(pos.x() - (200 / 2)), std::round(pos.y() - (100 /
    // 2)),
    //            200, 100);

    // qDebug() << "Rect = " << rect;

    // // QRectF rect(50, 50, 200, 100);
    // QImage image(rect.size(), QImage::Format_RGB32);
    // image.fill(Qt::transparent);  // clear the background

    // // 3. Initialize a QPainter on the image
    // QPainter painter(&image);
    // painter.setRenderHint(QPainter::Antialiasing);
    // // painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // qDebug() << "image.rect()" << image.rect();

    // render(&painter, image.rect(), rect);
    // painter.end();

    // m_magnifierWidget->setPixmap(QPixmap::fromImage(image));
    // m_magnifierProxyWidget->setVisible(true);

    QGraphicsScene::mouseMoveEvent(mouseEvent);
}
