#include "Widget.h"

#include <QDebug>
#include <QGraphicsGridLayout>
#include <QGraphicsLinearLayout>
#include <QGraphicsPixmapItem>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>
#include <QShowEvent>
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
    bindConnections();
}

void Widget::initGui() {
    // To show image correctly, size is important
    m_imageLabel->setMinimumSize(100, 100);

    m_rulerWidget = m_graphicsSecne->addWidget(new RulerWidget);
    m_imageWidget = m_graphicsSecne->addWidget(m_imageLabel);
    m_parameterWidget = m_graphicsSecne->addWidget(new ParameterWidget);

    // Don't use too many layouts, it will crop the display, if you want to
    // create a complex layout, please use QGraphicsGridLayout
    auto gridLayout = new QGraphicsGridLayout;
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->setSpacing(0);
    gridLayout->addItem(m_parameterWidget, 0, 0, 1, 2);
    gridLayout->addItem(m_rulerWidget, 1, 0);
    gridLayout->addItem(m_imageWidget, 1, 1);

    m_graphicsWidget = new QGraphicsWidget;
    m_graphicsWidget->setLayout(gridLayout);

    m_graphicsSecne->addItem(m_graphicsWidget);
    m_graphicsView->setScene(m_graphicsSecne);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_graphicsView);
    layout->addWidget(m_switchButton);
}

void Widget::bindConnections() {
    connect(m_switchButton, &QPushButton::clicked, this, [this] {
        static bool state = false;

        QString filePath = state ? "D:/2.png" : "D:/3.png";
        QPixmap pximap(filePath);
        m_imageLabel->setPixmap(pximap);
        m_imageWidget->setPreferredSize(pximap.size());

        state = !state;

        m_graphicsWidget->adjustSize();
        m_graphicsSecne->setSceneRect(m_graphicsWidget->boundingRect());
        m_graphicsView->fitInView(m_graphicsSecne->itemsBoundingRect(),
                                  Qt::KeepAspectRatio);
    });
}
