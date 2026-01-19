#pragma once

#include <QWidget>

class GraphicsView;
class GraphicsScene;
class QPushButton;
class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget* parent = nullptr);

private:
    void initGui();

    GraphicsScene* m_graphicsScene;
    GraphicsView* m_graphicsView;
    QPushButton* m_changePictureButton;
    QPushButton* m_zoomFactorButton;
};