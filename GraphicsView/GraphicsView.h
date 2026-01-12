#pragma once

#include <QGraphicsView>

class QGraphicsScreen;

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QGraphicsScene* scene, QWidget* parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event);
    void closeEvent(QCloseEvent* closeEvent);
};