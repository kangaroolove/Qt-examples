#pragma once

#include <MagnifierWidget.h>

#include <QGraphicsScene>
#include <memory>

class QLabel;

class GraphicsScene : public QGraphicsScene
{
public:
    GraphicsScene(QObject* parent = nullptr);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void keyPressEvent(QKeyEvent* keyEvent);

private:
    std::unique_ptr<MagnifierWidget> m_magnifierWidget;
    QPointF m_lastSceneMousePos;
};