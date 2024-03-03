#include "ServerWidget.h"
#include "Server.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QDebug>

ServerWidget::ServerWidget(QWidget* parent)
    : QWidget(parent)
    , m_receiveTextEdit(new QTextEdit(this))
    , m_sendTextEdit(new QTextEdit(this))
    , m_sendButton(new QPushButton("Send", this))
    , m_statusLabel(new QLabel(this))
    //, m_server(new Server(this))
{
    initGui();
    connect(m_sendButton, &QPushButton::clicked, this, [this]{
        //m_server->sendMessage(m_sendTextEdit->toPlainText());
        m_sendTextEdit->clear();
    });
    connect(m_server, &Server::receiveMessage, this, [this](const QString& msg){
        m_receiveTextEdit->append(msg);
    });
    startServer();
}

ServerWidget::~ServerWidget()
{

}

void ServerWidget::initGui()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel* receiveLabel = new QLabel("Receive:", this);
    QLabel* sendLabel = new QLabel("Send:", this);

    layout->addWidget(m_statusLabel);
    layout->addWidget(receiveLabel);
    layout->addWidget(m_receiveTextEdit);
    layout->addWidget(sendLabel);
    layout->addWidget(m_sendTextEdit);
    layout->addWidget(m_sendButton);
}

void ServerWidget::startServer()
{
    // if (!m_server->start())
    //     qDebug()<<"Server listen error";
    // else 
    //     m_statusLabel->setText("Start listening");
}
