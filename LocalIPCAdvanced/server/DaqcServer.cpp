#include "DaqcServer.h"
#include "DaqcServerHandleReceiveMessageTask.h"
#include "SendTask.h"
#include "DaqcClientDef.h"
#include "GetInfoPacket.h"
#include "ServerWorker.h"
#include "RequestUpdatePacket.h"
#include "ResourceManager.h"
#include "FramePacket.h"
#include <QThreadPool>
#include <QDebug>
#include <QTimer>
#include <QJsonDocument>

DaqcServer::DaqcServer(QObject* parent) :
    Server(parent),
    m_worker(new ServerWorker),
    m_thread(new QThread(this))
{
    m_worker->moveToThread(m_thread);
    connect(m_thread, &QThread::finished, m_worker, &ServerWorker::deleteLater);
    connect(this, &DaqcServer::handleUpdateRequest, m_worker, &ServerWorker::handleUpdateRequest);
    connect(m_worker, &ServerWorker::uploadImageFinished, this, &DaqcServer::uploadImageFinished);
    m_thread->start();
}

DaqcServer::~DaqcServer()
{
    m_thread->quit();
    m_thread->wait();
}

void DaqcServer::start()
{
    auto result = listen("cms/daqc");
    if (result)
        qInfo()<<"Daqc server started";
    else 
        qCritical()<<"Daqc server started failed";
}

HandleReceiveMessageTask *DaqcServer::generateHandleRequestTask(const QByteArray& data)
{
    return nullptr;
}

void DaqcServer::uploadImageFinished()
{
    auto packet = new FramePacket();
    sendMessage(packet->toBinary());
}

void DaqcServer::handleReceive(const QByteArray &data)
{
    auto document = QJsonDocument::fromJson(data);
    if (document.isNull())
        return;

    QString packetType = getPacketType(document);
    if (packetType == PacketType::REQUEST)
    {
        auto requestType = getRequestType(document);
        if (requestType == "update")
        {
            auto packet = RequestUpdatePacket::fromJson(document.object());
            emit handleUpdateRequest(packet.getParameter(), packet.getValueTypes(), packet.getValues());
        }
    }
}

// void DaqcServer::frameReady(const QImage& image)
// {
//     // GetInfoPacket* packet = new GetPacket(ResourceManager::getInstance()->getDaqcInfo(), image);
//     // sendMessage(packet->toBinary());
// }

QString DaqcServer::getPacketType(const QJsonDocument &document) const
{
    return document["packetType"].toString();
}

QString DaqcServer::getRequestType(const QJsonDocument &document) const
{
    return document["data"].toObject()["requestType"].toString();
}