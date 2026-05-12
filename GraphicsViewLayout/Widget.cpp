#include "Widget.h"

#include <QDebug>
#include <QGraphicsLinearLayout>
#include <QGraphicsPixmapItem>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "ParameterWidget.h"
#include "RulerWidget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_graphicsView(new QGraphicsView(this)),
      m_graphicsSecne(new QGraphicsScene),
      m_switchButton(new QPushButton("Switch", this)),
      m_imageLabel(new QLabel()) {
    initGui();
}

void Widget::initGui() {
    QPixmap pixmap("D:/2.png");
    m_imageLabel->setPixmap(pixmap);

    m_graphicsSecne->setSceneRect(0, 0, 1920, 1080);

    m_rulerWidget = m_graphicsSecne->addWidget(new RulerWidget);
    m_parameterWidget = m_graphicsSecne->addWidget(new ParameterWidget);
    m_imageWidget = m_graphicsSecne->addWidget(m_imageLabel);
    // m_imagePixmap = m_graphicsSecne->addPixmap(pixmap);

    auto linearLayout = new QGraphicsLinearLayout;
    linearLayout->setContentsMargins(0, 0, 0, 0);
    linearLayout->setSpacing(0);
    linearLayout->setOrientation(Qt::Horizontal);
    linearLayout->addItem(m_rulerWidget);
    linearLayout->addItem(m_imageWidget);
    linearLayout->addItem(m_parameterWidget);
    // linearLayout->setMinimumSize(400, 300);

    auto w = new QGraphicsWidget;
    w->setLayout(linearLayout);

    m_graphicsSecne->addItem(w);

    m_graphicsView->setScene(m_graphicsSecne);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_graphicsView);
    layout->addWidget(m_switchButton);
}
