#include "Widget.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_graphicsView(new QGraphicsView(this)),
      m_graphicsSecne(new QGraphicsScene),
      m_switchButton(new QPushButton("Switch", this)) {
    initGui();
}

void Widget::initGui() {
    m_graphicsView->setScene(m_graphicsSecne);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_graphicsView);
    layout->addWidget(m_switchButton);
}
