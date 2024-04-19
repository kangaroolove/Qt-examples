#include "DaqcServer.h"
#include "DaqcServerHandleReceiveMessageTask.h"
#include "SendTask.h"
#include "DaqcClientDef.h"
#include "GetInfoPacket.h"
#include "ServerWorker.h"
#include "RequestUpdatePacket.h"
#include "ResourceManager.h"
#include "FramePacket.h"
#include "ResourceManager.h"
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

HandleReceiveMessageTask *DaqcServer::generateHandleRequestTask(const QByteArray &data)
{
    return nullptr;
}

void DaqcServer::uploadImageFinished()
{
    sendFrame();
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

QString DaqcServer::getPacketType(const QJsonDocument &document) const
{
    return document["packetType"].toString();
}

QString DaqcServer::getRequestType(const QJsonDocument &document) const
{
    return document["data"].toObject()["requestType"].toString();
}

void DaqcServer::sendFrame()
{
    auto packet = new FramePacket(ResourceManager::getInstance()->getDaqcInfo());
    sendMessage(packet->toBinary());
}
