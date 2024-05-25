#include "Widget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStateMachine>
#include <QState>
#include <QDebug>
#include <QLabel>

Widget::Widget(QWidget * parent)
    : QWidget(parent)
    , m_stateMachine(new QStateMachine(this))
{
    initGui();
    initStateMachine();
}

Widget::~Widget()
{

}

void Widget::initGui()
{
    m_btnS1 = new QPushButton("S1", this);
    m_btnS2 = new QPushButton("S2", this);
    m_btnS3 = new QPushButton("S3", this);

    auto buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(m_btnS1);
    buttonLayout->addWidget(m_btnS2);
    buttonLayout->addWidget(m_btnS3);

    m_label = new QLabel();

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(m_label);

    resize(400, 300);
}

void Widget::bindConnections()
{
}

void Widget::initStateMachine()
{
    auto mainState = new QState;
    auto s1 = new QState(mainState);
    auto s2 = new QState(mainState);
    auto s3 = new QState(mainState);

    s1->assignProperty(m_label, "text", "In state s1");
    s2->assignProperty(m_label, "text", "In state s2");
    s3->assignProperty(m_label, "text", "In state s3");

    mainState->setInitialState(s1);

    mainState->addTransition(m_btnS1, &QPushButton::clicked, s1);
    mainState->addTransition(m_btnS2, &QPushButton::clicked, s2);
    mainState->addTransition(m_btnS3, &QPushButton::clicked, s3);

    connect(s1, &QState::entered, this, [this]{
        qDebug()<<"Enter s1";
    });
    connect(s2, &QState::entered, this, [this]{
        qDebug()<<"Enter s2";
    });
    connect(s3, &QState::entered, this, [this]{
        qDebug()<<"Enter s3";
    });

    m_stateMachine->addState(mainState);
    m_stateMachine->setInitialState(mainState);
    m_stateMachine->start();
}
