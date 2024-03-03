#include "ClientWidget.h"
#include "DaqcClient.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QDebug>

ClientWidget::ClientWidget(QWidget* parent)
    : QWidget(parent)
    , m_receiveTextEdit(new QTextEdit(this))
    , m_sendTextEdit(new QTextEdit(this))
    , m_sendButton(new QPushButton("Send", this))
    , m_client(new DaqcClient(this))
{
    initGui();
    connect(m_sendButton, &QPushButton::clicked, this, [this]{
        //m_client->sendMessage(m_sendTextEdit->toPlainText());
        //m_sendTextEdit->clear();

        m_client->testSetApi(true);
    });
    connect(m_client, &Client::receiveMessage, this, [this](const QString& msg){
        m_receiveTextEdit->append(msg);
    });

    m_client->start();
}

ClientWidget::~ClientWidget()
{

}

void ClientWidget::initGui()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel* receiveLabel = new QLabel("Receive:", this);
    QLabel* sendLabel = new QLabel("Send:", this);

    layout->addWidget(receiveLabel);
    layout->addWidget(m_receiveTextEdit);
    layout->addWidget(sendLabel);
    layout->addWidget(m_sendTextEdit);
    layout->addWidget(m_sendButton);
}