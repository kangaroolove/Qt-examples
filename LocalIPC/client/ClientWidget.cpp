#include "ClientWidget.h"
#include "Client.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

ClientWidget::ClientWidget(QWidget *parent)
    : QWidget(parent),
      m_receiveTextEdit(new QTextEdit(this)),
      m_sendTextEdit(new QTextEdit(this)),
      m_sendButton(new QPushButton("Send", this)),
      m_client(new Client(this)) {
    initGui();
    bindConnections();
    connectServer();
}

void ClientWidget::initGui() {
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *receiveLabel = new QLabel("Receive:", this);
    QLabel *sendLabel = new QLabel("Send:", this);

    layout->addWidget(receiveLabel);
    layout->addWidget(m_receiveTextEdit);
    layout->addWidget(sendLabel);
    layout->addWidget(m_sendTextEdit);
    layout->addWidget(m_sendButton);
}

void ClientWidget::connectServer() {
    m_client->connectToServer("KangarooLove");
}

void ClientWidget::bindConnections() {
    connect(m_sendButton, &QPushButton::clicked, this, [this] {
        m_client->sendMessage(m_sendTextEdit->toPlainText());
        m_sendTextEdit->clear();
    });
    connect(m_client, &Client::receiveMessage, this,
            [this](const QString &msg) { m_receiveTextEdit->append(msg); });
}
