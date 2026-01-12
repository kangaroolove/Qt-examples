#include "GraphicsScene.h"

#include <QDebug>
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QPainter>

GraphicsScene::GraphicsScene(QObject* parent)
    : QGraphicsScene(parent),
      m_magnifierWidget(std::make_unique<MagnifierWidget>()) {
    QPixmap pixmap("D:/2.jpg");
    auto pixmapItem = addPixmap(pixmap);
    pixmapItem->setTransformationMode(Qt::SmoothTransformation);

    addText("Hello, world");

    auto text2 = addText("Second Text");
    text2->setPos(40, 40);

    m_magnifierWidget->move(0, 0);
    m_magnifierWidget->show();
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    // // if ((pos.x() >= 200 / 2 || pos.x() <= 1280 - (200 / 2)) &&
    // //         pos.y() >= 100 / 2 ||
    // //     pos.y() <= 720 - (100 / 2))
    // m_magnifierProxyWidget->setPos(pos.x() - (200 / 2), pos.y() - (100 / 2));

    auto scenePos = mouseEvent->scenePos();

    auto scale = 0.797765;

    auto width = m_magnifierWidget->getZoomSize().width();
    auto height = m_magnifierWidget->getZoomSize().height();

    QRectF rect(scenePos.x() - (width / 2), scenePos.y() - (height / 2), width,
                height);

    QImage image(width * scale, height * scale, QImage::Format_ARGB32);
    image.fill(Qt::transparent);  // clear the background

    // 3. Initialize a QPainter on the image
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    render(&painter, image.rect(), rect);
    painter.end();

    // qDebug() << image.rect();

    m_magnifierWidget->setPixmap(QPixmap::fromImage(image));

    // QRectF rect((scenePos.x() - (width / 2) / 0.797765),
    //             (scenePos.y() - (height / 2) / 0.797765), width /
    // 0.797765,
    //             height / 0.797765);

    // QRectF rect(0, 0, width / scale, height / scale);

    // QImage image(width, height, QImage::Format_ARGB32);
    // image.fill(Qt::transparent);  // clear the background

    // // 3. Initialize a QPainter on the image
    // QPainter painter(&image);
    // painter.setRenderHint(QPainter::Antialiasing);
    // painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // render(&painter, image.rect(), rect);
    // painter.end();

    // auto screenPos = mouseEvent->screenPos();
    // auto newX = (screenPos.x() - (width / 2));
    // auto newY = (screenPos.y() - (height / 2));
    // // m_magnifierWidget->move(newX, newY);

    // m_magnifierWidget->setPixmap(QPixmap::fromImage(image));

    // m_lastSceneMousePos = mouseEvent->scenePos();

    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void GraphicsScene::keyPressEvent(QKeyEvent* keyEvent) {
    if (keyEvent->key() == Qt::Key_H) {
        // auto width = m_magnifierWidget->width();
        // auto height = m_magnifierWidget->height();

        // auto scale = 0.797765;

        // QRectF rect(0, 0, width, height);

        // QImage image(width, height, QImage::Format_ARGB32);
        // image.fill(Qt::transparent);  // clear the background

        // // 3. Initialize a QPainter on the image
        // QPainter painter(&image);
        // painter.setRenderHint(QPainter::Antialiasing);
        // painter.setRenderHint(QPainter::SmoothPixmapTransform);

        // render(&painter, image.rect(), rect);
        // painter.end();

        // qDebug() << image.rect();

        // auto convertImage =
        //     image.scaled(image.width() * scale, image.height() * scale,
        //                  Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // convertImage.save("D:/5.png");
    }

    else if (keyEvent->key() == Qt::Key_M) {
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
