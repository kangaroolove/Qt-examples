#pragma once

#include <QGraphicsView>

class QGraphicsScreen;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(QGraphicsScene* scene, QWidget* parent = nullptr);
signals:
    void fitInViewScaleChanged(double scale);

protected:
    void resizeEvent(QResizeEvent* event);
    void closeEvent(QCloseEvent* closeEvent);

private:
    double m_fitInViewScale;
};