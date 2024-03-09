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
    m_client(new Client()),
    m_thread(new QThread(this))
{
    m_client->moveToThread(m_thread);
    connect(m_thread, &QThread::finished, m_client, &Client::deleteLater);
    connect(this, &DaqcClient::sendMessage, m_client, &Client::sendMessage);
    connect(this, &DaqcClient::connectServer, m_client, &Client::connectServer);
    connect(m_client, &Client::receiveMessage, this, &DaqcClient::receiveMessage);
    m_thread->start();
}

DaqcClient::~DaqcClient()
{
    m_thread->quit();
    m_thread->wait();
}

void DaqcClient::start()
{
    emit connectServer();
    qDebug()<<"Connect to server";
}

int DaqcClient::testGetApi()
{
    auto result = createGetRequest([]{ 
        return new RequestGetPacket("test"); 
    });
    return result.toInt();
}

void DaqcClient::testSetApi(bool isTest)
{
    createUpdateRequest(new RequestUpdatePacket("test", isTest, "bool"));
}

QVariant DaqcClient::createGetRequest(std::function<Packet*()> callback)
{
    QEventLoop eventloop;
    connect(m_client, &Client::quitEventloop, &eventloop, &QEventLoop::quit);

    Packet* packet = callback();
    emit sendMessage(packet->toJson());
    eventloop.exec();

    RequestResult result = m_client->getRequestResult(packet->getMessageId());
    packet->deleteLater();
    return result.value;
}

void DaqcClient::createUpdateRequest(Packet *packet)
{
    emit sendMessage(packet->toJson());
    packet->deleteLater();
}
