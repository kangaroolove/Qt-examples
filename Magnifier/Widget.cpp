#include "Widget.h"

#include <QCloseEvent>
#include <QCoreApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStateMachine>
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
    initMagnifierStateMachine();
    bindConnections();
    onChangePictureButtonClicked();
    resize(800, 600);
}

void Widget::closeEvent(QCloseEvent* closeEvent) { QCoreApplication::quit(); }

void Widget::onChangePictureButtonClicked() {
    static bool clicked = false;
    // 2.png:1920 * 1080, 2,jpg:1044 * 895
    clicked ? m_graphicsScene->setImage(QPixmap("D:/2.png"))
            : m_graphicsScene->setImage(QPixmap("D:/2.jpg"));
    clicked = !clicked;
}

void Widget::initGui() {
    auto buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(m_zoomFactorButton);
    buttonLayout->addWidget(m_changePictureButton);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_graphicsView);
    layout->addLayout(buttonLayout);
}

void Widget::bindConnections() {
    connect(m_graphicsView, &GraphicsView::fitInViewScaleChanged,
            m_graphicsScene, &GraphicsScene::onFitInViewScaleChanged);
    connect(m_changePictureButton, &QPushButton::clicked, this,
            &Widget::onChangePictureButtonClicked);
}

void Widget::initMagnifierStateMachine() {
    auto x1Magnification = new QState;
    auto x2Magnification = new QState;
    auto x4Magnification = new QState;

    x1Magnification->addTransition(m_zoomFactorButton, &QPushButton::clicked,
                                   x2Magnification);
    x2Magnification->addTransition(m_zoomFactorButton, &QPushButton::clicked,
                                   x4Magnification);
    x4Magnification->addTransition(m_zoomFactorButton, &QPushButton::clicked,
                                   x1Magnification);

    x1Magnification->assignProperty(m_zoomFactorButton, "text", "ZOOM:X1");
    x2Magnification->assignProperty(m_zoomFactorButton, "text", "ZOOM:X2");
    x4Magnification->assignProperty(m_zoomFactorButton, "text", "ZOOM:X4");

    connect(x1Magnification, &QState::entered, m_graphicsScene,
            &GraphicsScene::magnifyAreaOneTime);
    connect(x2Magnification, &QState::entered, m_graphicsScene,
            &GraphicsScene::magnifyAreaTwoTimes);
    connect(x4Magnification, &QState::entered, m_graphicsScene,
            &GraphicsScene::magnifyAreaFourTimes);

    std::vector<QState*> states = {x1Magnification, x2Magnification,
                                   x4Magnification};
    for (auto state : states) {
        m_magnifierStateMachine.addState(state);
    }
    m_magnifierStateMachine.setInitialState(x1Magnification);
    m_magnifierStateMachine.start();
}
