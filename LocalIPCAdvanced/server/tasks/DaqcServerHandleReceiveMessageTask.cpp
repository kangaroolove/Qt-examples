#include "DaqcServerHandleReceiveMessageTask.h"
#include "SendTask.h"
#include "PacketFactory.h"
#include "Server.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QUuid>
#include <QThreadPool>

DaqcServerHandleReceiveMessageTask::DaqcServerHandleReceiveMessageTask(Server* server, const QByteArray& data) :
    HandleReceiveMessageTask(data),
    m_server(server),
    m_packetFactory(new PacketFactory(this))
{

}

DaqcServerHandleReceiveMessageTask::~DaqcServerHandleReceiveMessageTask()
{

}

void DaqcServerHandleReceiveMessageTask::analyzeJson(const QByteArray &data)
{
    auto document = QJsonDocument::fromJson(data);
    if (document.isNull())
        return;

    handleTask(getParameter(document), getRequestType(document), getClientMessageId(document));
}

void DaqcServerHandleReceiveMessageTask::handleTask(const QString &parameter, const QString &requestType, const QString &clientMessageId)
{
    qDebug()<<"parameter = "<< parameter;
    qDebug()<<"requestType = "<< requestType;
    qDebug()<<"clientMessageId = "<< clientMessageId<<"\n";

    auto packet = m_packetFactory->createReplyPacket(parameter, requestType, clientMessageId);
    if (packet)
    {
        auto task = new SendTask(packet);
        connect(task, &SendTask::sendMessage, m_server, &Server::sendMessage, Qt::QueuedConnection);
        QThreadPool::globalInstance()->start(task);
    }
}

QString DaqcServerHandleReceiveMessageTask::getRequestType(const QJsonDocument &document)
{
    return document["data"].toObject()["requestType"].toString();
}

QString DaqcServerHandleReceiveMessageTask::getClientMessageId(const QJsonDocument &document)
{
    return document["messageId"].toString();
}

QString DaqcServerHandleReceiveMessageTask::getParameter(const QJsonDocument &document)
{
    return document["data"].toObject()["parameter"].toString();
}
