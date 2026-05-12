#include "Widget.h"

#include <QDebug>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QVBoxLayout>

#include "RulerWidget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_graphicsView(new QGraphicsView(this)),
      m_graphicsSecne(new QGraphicsScene),
      m_switchButton(new QPushButton("Switch", this)) {
    initGui();
}

void Widget::initGui() {
    m_rulerWidget = m_graphicsSecne->addWidget(new RulerWidget);

    m_graphicsView->setScene(m_graphicsSecne);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_graphicsView);
    layout->addWidget(m_switchButton);
}
