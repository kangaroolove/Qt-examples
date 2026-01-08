#include "GraphicsScene.h"

#include <QGraphicsProxyWidget>

#include "Widget.h"

GraphicsScene::GraphicsScene(QObject* parent) : QGraphicsScene(parent) {
    QPixmap pixmap("D:/1.jpg");
    addPixmap(pixmap);

    addText("Hello, world");

    auto text2 = addText("Second Text");
    text2->setPos(50, 50);

    auto widget = new Widget;
    m_zoomWidget = addWidget(widget);
}