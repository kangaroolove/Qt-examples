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
    , m_server(new Server(this))
    , m_openButton(new QPushButton("Open file", this))
    , m_clearButton(new QPushButton("Clear file list", this))
    , m_fileListTextEdit(new QTextEdit(this))
    , m_timerGapLabel(new QLabel("Timer interval:", this))
    , m_timerInput(new QLineEdit(this))
    , m_timerGapUnitLabel(new QLabel("ms", this))
    , m_sendButton(new QPushButton("Send", this))
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
    // auto text = m_sendTextEdit->toPlainText();
    // if (text.isEmpty())
    // {
    //     QMessageBox::critical(this, "Critical", "You didn't type anything!");
    //     return;
    // }

    // auto interval = m_timerIntervalInput->text();
    // if (interval.isEmpty())
    // {
    //     QMessageBox::critical(this, "Critical", "You didn't enter the timer interval!");
    //     return;
    // }

    // m_timer = std::make_unique<QTimer>();
    // m_timer->setInterval(interval.toInt());
    // connect(m_timer.get(), &QTimer::timeout, this, &ServerWidget::onSendButtonClicked);
    // m_timer->start();
}

void ServerWidget::onSendButtonClicked()
{
    // auto text = m_sendTextEdit->toPlainText();
    // if (text.isEmpty())
    // {
    //     QMessageBox::critical(this, "Critical", "You didn't type anything!");
    //     return;
    // }
    
    // m_server->sendMessage(text);
}

void ServerWidget::initGui()
{
    auto layout = new QVBoxLayout(this);
    layout->addLayout(getFileButtonLayout());
    layout->addWidget(m_fileListTextEdit);
    layout->addLayout(getTimerLayout());
    layout->addWidget(m_sendButton);

    m_fileListTextEdit->setReadOnly(true);
    m_timerInput->setText("16");
}

void ServerWidget::startServer()
{
    // if (!m_server->start())
    //     qDebug()<<"Server listen error";
    // else 
    //     m_statusLabel->setText("Start listening");
}

void ServerWidget::bindConnections()
{
    // connect(m_sendButton, &QPushButton::clicked, this, &ServerWidget::onSendButtonClicked);
    // connect(m_server, &Server::receiveMessage, this, [this](const QString& msg){
    //     m_receiveTextEdit->append(msg);
    // });
    // connect(m_autoSendButton, &QPushButton::clicked, this, &ServerWidget::onAutoSendButtonClicked);
    // connect(m_stopSendButton, &QPushButton::clicked, this, [this]{
    //     m_timer->stop();
    // });
}

QHBoxLayout *ServerWidget::getFileButtonLayout()
{
    auto layout = new QHBoxLayout();
    layout->addWidget(m_openButton);
    layout->addWidget(m_clearButton);
    return layout;
}

QHBoxLayout *ServerWidget::getTimerLayout()
{
    auto layout = new QHBoxLayout();
    layout->addWidget(m_timerGapLabel);
    layout->addWidget(m_timerInput);
    layout->addWidget(m_timerGapUnitLabel);
    return layout;
}
