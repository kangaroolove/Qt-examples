#include "ServerWidget.h"
#include "Server.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QTimer>
#include <QMessageBox>

ServerWidget::ServerWidget(QWidget* parent) : 
QWidget(parent)
    , m_receiveTextEdit(new QTextEdit(this))
    , m_sendTextEdit(new QTextEdit(this))
    , m_sendButton(new QPushButton("Send", this))
    , m_statusLabel(new QLabel(this))
    , m_server(new Server(this))
    , m_timerIntervalInput(new QLineEdit(this))
    , m_autoSendButton(new QPushButton("Auto send"))
    , m_stopSendButton(new QPushButton("Stop"))
{
    initGui();
    bindConnections();
    startServer();
}

ServerWidget::~ServerWidget()
{

}

void ServerWidget::onAutoSendButtonClicked()
{
    auto text = m_sendTextEdit->toPlainText();
    if (text.isEmpty())
    {
        QMessageBox::critical(this, "Critical", "You didn't type anything!");
        return;
    }

    auto interval = m_timerIntervalInput->text();
    if (interval.isEmpty())
    {
        QMessageBox::critical(this, "Critical", "You didn't enter the timer interval!");
        return;
    }

    m_timer = std::make_unique<QTimer>();
    m_timer->setInterval(interval.toInt());
    connect(m_timer.get(), &QTimer::timeout, this, &ServerWidget::onSendButtonClicked);
    m_timer->start();
}

void ServerWidget::onSendButtonClicked()
{
    auto text = m_sendTextEdit->toPlainText();
    if (text.isEmpty())
    {
        QMessageBox::critical(this, "Critical", "You didn't type anything!");
        return;
    }
    
    m_server->sendMessage(text);
}

void ServerWidget::initGui()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel* receiveLabel = new QLabel("Receive:", this);
    QLabel* sendLabel = new QLabel("Send:", this);

    m_timerIntervalInput->setPlaceholderText("ms");

    layout->addWidget(m_statusLabel);
    layout->addWidget(receiveLabel);
    layout->addWidget(m_receiveTextEdit);
    layout->addWidget(sendLabel);
    layout->addWidget(m_sendTextEdit);
    layout->addWidget(m_sendButton);
    layout->addLayout(getTimerLayout());
}

void ServerWidget::startServer()
{
    if (!m_server->start())
        qDebug()<<"Server listen error";
    else 
        m_statusLabel->setText("Start listening");
}

void ServerWidget::bindConnections()
{
    connect(m_sendButton, &QPushButton::clicked, this, &ServerWidget::onSendButtonClicked);
    connect(m_server, &Server::receiveMessage, this, [this](const QString& msg){
        m_receiveTextEdit->append(msg);
    });
    connect(m_autoSendButton, &QPushButton::clicked, this, &ServerWidget::onAutoSendButtonClicked);
    connect(m_stopSendButton, &QPushButton::clicked, this, [this]{
        m_timer->stop();
    });
}

QHBoxLayout *ServerWidget::getTimerLayout()
{
    auto layout = new QHBoxLayout();
    auto timerLabel = new QLabel("Sending gap:");
    layout->addWidget(timerLabel);
    layout->addWidget(m_timerIntervalInput);
    layout->addWidget(m_autoSendButton);
    layout->addWidget(m_stopSendButton);
    return layout;
}
