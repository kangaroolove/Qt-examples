#pragma once

#include <MagnifierWidget.h>

#include <QGraphicsScene>
#include <memory>

class QLabel;
class QGraphicsPixmapItem;

class GraphicsScene : public QGraphicsScene
{
public:
    GraphicsScene(QObject* parent = nullptr);
    void setImage(const QPixmap& pix);

public slots:
    void onFitInViewScaleChanged(double scale);
    void magnifyAreaOneTime();
    void magnifyAreaTwoTimes();
    void magnifyAreaFourTimes();

protected:
    // void keyPressEvent(QKeyEvent* keyEvent);
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    void moveMagnifierWidget(const QPoint& screenPos);
    void updateMagnifierDisplayPicture(const QPointF& scenePos);
    void updateMagnifierWidgetSize(const double& fitInViewScale);

    std::unique_ptr<MagnifierWidget> m_magnifierWidget;
    double m_fitInViewScale;
    bool m_canMoveMagnifier;
    QGraphicsPixmapItem* m_pixmapItem;
};