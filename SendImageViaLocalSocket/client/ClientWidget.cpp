#include "ClientWidget.h"
#include "Client.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QThread>

ClientWidget::ClientWidget(QWidget* parent)
    : QWidget(parent)
    , m_displayLabel(new QLabel("There is no image", this))
    , m_client(new Client())
    , m_clientThread(new QThread(this))
{
    initGui();
    bindConnections();
    initWorker();
    connectServer();
}

ClientWidget::~ClientWidget()
{
    m_clientThread->quit();
    m_clientThread->wait();
}

void ClientWidget::initGui()
{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_displayLabel);
    resize(800, 400);
}

void ClientWidget::connectServer()
{
    emit connectToServer();
}

void ClientWidget::bindConnections()
{
    connect(m_client, &Client::receiveImage, this, [this](QImage image){
        m_displayLabel->setPixmap(QPixmap::fromImage(image));
    }, Qt::QueuedConnection);
}

void ClientWidget::initWorker()
{
    m_client->moveToThread(m_clientThread);
    connect(m_clientThread, &QThread::finished, m_client, &Client::deleteLater);
    connect(this, &ClientWidget::connectToServer, m_client, &Client::connectServer);
    m_clientThread->start();
}
