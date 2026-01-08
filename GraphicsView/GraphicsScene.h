#pragma once

#include <QGraphicsScene>

class GraphicsScene : public QGraphicsScene
{
public:
    GraphicsScene(QObject* parent = nullptr);

private:
    QGraphicsProxyWidget* m_zoomWidget;
};