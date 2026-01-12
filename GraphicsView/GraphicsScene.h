#pragma once

#include <MagnifierWidget.h>

#include <QGraphicsScene>
#include <memory>

class QLabel;

class GraphicsScene : public QGraphicsScene
{
public:
    GraphicsScene(QObject* parent = nullptr);

public slots:
    void onFitInViewScaleChanged(double scale);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void keyPressEvent(QKeyEvent* keyEvent);
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    void moveMagnifierWidget(const QPoint& screenPos);
    void updateMagnifierDisplayPicture(const QPointF& scenePos);
    void updateMagnifierWidgetSize(const double& fitInViewScale);

    std::unique_ptr<MagnifierWidget> m_magnifierWidget;
    QPointF m_lastSceneMousePos;
    double m_fitInViewScale;
};