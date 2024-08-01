#include "ClientWidget.h"
#include "Client.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QDebug>

ClientWidget::ClientWidget(QWidget* parent)
    : QWidget(parent)
    , m_displayLabel(new QLabel("There is no image", this))
    , m_client(new Client(this))
{
    initGui();
    bindConnections();
    connectServer();
}

ClientWidget::~ClientWidget()
{

}

void ClientWidget::initGui()
{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_displayLabel);
    resize(800, 400);
}

void ClientWidget::connectServer()
{
    m_client->connectToServer("KangarooLove");
}

void ClientWidget::bindConnections()
{
    connect(m_client, &Client::receiveImage, this, [this](QImage image){
        m_displayLabel->setPixmap(QPixmap::fromImage(image));
    });
}
