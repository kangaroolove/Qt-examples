#pragma once

#include <QWidget>

class QGraphicsView;
class QGraphicsScene;
class QPushButton;
class QGraphicsProxyWidget;
class QGraphicsPixmapItem;
class QLabel;
class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);

private:
    void initGui();

    QGraphicsView* m_graphicsView;
    QGraphicsScene* m_graphicsSecne;
    QPushButton* m_switchButton;
    QGraphicsProxyWidget* m_rulerWidget;
    QGraphicsProxyWidget* m_parameterWidget;
    QLabel* m_imageLabel;
    QGraphicsProxyWidget* m_imageWidget;
};