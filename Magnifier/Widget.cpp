#include "Widget.h"

#include <QCloseEvent>
#include <QCoreApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

#include "GraphicsScene.h"
#include "GraphicsView.h"

Widget::Widget(QWidget* parent)
    : QWidget(parent),
      m_graphicsScene(new GraphicsScene()),
      m_graphicsView(new GraphicsView(m_graphicsScene)),
      m_changePictureButton(new QPushButton("Change picture")),
      m_zoomFactorButton(new QPushButton()) {
    initGui();
    connect(m_graphicsView, &GraphicsView::fitInViewScaleChanged,
            m_graphicsScene, &GraphicsScene::onFitInViewScaleChanged);
}

void Widget::closeEvent(QCloseEvent* closeEvent) { QCoreApplication::quit(); }

void Widget::initGui() {
    auto buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(m_zoomFactorButton);
    buttonLayout->addWidget(m_changePictureButton);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_graphicsView);
    layout->addLayout(buttonLayout);
}
