#pragma once

#include <QGraphicsScene>

class QLabel;

class GraphicsScene : public QGraphicsScene
{
public:
    GraphicsScene(QObject* parent = nullptr);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);

private:
    QGraphicsProxyWidget* m_magnifierProxyWidget;
    QLabel* m_magnifierWidget;
};