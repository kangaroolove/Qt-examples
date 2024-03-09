#include "DaqcClient.h"
#include "RequestGetPacket.h"
#include "RequestUpdatePacket.h"
#include "Client.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QThreadPool>
#include <QEventLoop>

DaqcClient::DaqcClient(QObject* parent) :
    m_eventLoop(new QEventLoop(this)),
    m_client(new Client(m_eventLoop)),
    m_thread(new QThread(this))
{
    m_client->moveToThread(m_thread);
    connect(this, &DaqcClient::sendMessage, m_client, &Client::sendMessage);
    connect(this, &DaqcClient::connectServer, m_client, &Client::connectServer);
    connect(m_client, &Client::receiveMessage, this, &DaqcClient::receiveMessage);
    m_thread->start();
}

DaqcClient::~DaqcClient()
{

}

void DaqcClient::start()
{
    emit connectServer();
    qDebug()<<"Connect to server";
}

int DaqcClient::testGetApi()
{
    auto packet = new RequestGetPacket("test");
    emit sendMessage(packet->toJson());
    m_eventLoop->exec();

    auto result = m_client->getRequestResult(packet->getMessageId());
    if (result.valueType == "int")
        return result.value.toInt();
        
    return 0;
}

void DaqcClient::testSetApi(bool isTest)
{
    auto packet = new RequestUpdatePacket("test", isTest, "bool");
    emit sendMessage(packet->toJson());
}
