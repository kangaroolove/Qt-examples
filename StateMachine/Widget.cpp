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
    m_btnS4 = new QPushButton("SecondMain", this);

    auto buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(m_btnS1);
    buttonLayout->addWidget(m_btnS2);
    buttonLayout->addWidget(m_btnS3);
    buttonLayout->addWidget(m_btnS4);

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
    auto rootState = new QState();
    auto mainState = new QState(rootState);
    auto secondState = new QState(rootState);

    auto s1 = new QState(mainState);
    auto s2 = new QState(mainState);
    auto s3 = new QState(mainState);

    s1->assignProperty(m_label, "text", "In state s1");
    s2->assignProperty(m_label, "text", "In state s2");
    s3->assignProperty(m_label, "text", "In state s3");

    mainState->setInitialState(s1);
    rootState->setInitialState(mainState);

    connect(mainState, &QState::entered, this, [this]{
        qDebug()<<"Enter main state";
    });

    connect(mainState, &QState::exited, this, [this]{
        qDebug()<<"Exit main state";
    });

    rootState->addTransition(m_btnS1, &QPushButton::clicked, s1);
    rootState->addTransition(m_btnS2, &QPushButton::clicked, s2);
    rootState->addTransition(m_btnS3, &QPushButton::clicked, s3);
    rootState->addTransition(m_btnS4, &QPushButton::clicked, secondState);

    connect(s1, &QState::entered, this, [this]{
        qDebug()<<"Enter s1";
    });
    connect(s2, &QState::entered, this, [this]{
        qDebug()<<"Enter s2";
    });
    connect(s3, &QState::entered, this, [this]{
        qDebug()<<"Enter s3";
    });

    m_stateMachine->addState(rootState);
    m_stateMachine->setInitialState(rootState);
    m_stateMachine->start();
}
