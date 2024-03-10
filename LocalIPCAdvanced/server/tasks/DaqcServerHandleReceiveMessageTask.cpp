#include "DaqcServerHandleReceiveMessageTask.h"
#include "SendTask.h"
#include "PacketFactory.h"
#include "Server.h"
#include "UpdateValueTask.h"
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

    QString parameter = getParameter(document);
    QString requestType = getRequestType(document);
    QString clientMessageId = getRequestType(document);
    QString valueType = getValueType(document);
    QVariant value = getValue(document);

    qDebug()<<"parameter = "<< parameter;
    qDebug()<<"requestType = "<< requestType;
    qDebug()<<"clientMessageId = "<< clientMessageId;
    qDebug()<<"valueType = "<< valueType;
    qDebug()<<"value = "<< value <<"\n";
    
    if (requestType == "get")
        handleGetRequest(parameter, clientMessageId);
    else if (requestType == "update")
        handleUpdateRequest(parameter, valueType, value);
}

void DaqcServerHandleReceiveMessageTask::handleGetRequest(const QString &parameter, const QString &clientMessageId)
{
    auto packet = m_packetFactory->createReplyPacket(parameter, clientMessageId);
    if (packet)
    {
        auto task = new SendTask(packet);
        connect(task, &SendTask::sendMessage, m_server, &Server::sendMessage, Qt::QueuedConnection);
        QThreadPool::globalInstance()->start(task);
    }
}

void DaqcServerHandleReceiveMessageTask::handleUpdateRequest(const QString &parameter, const QString &valueType, const QVariant &value)
{
    UpdateValueInfo info;
    info.parameter = parameter;
    info.value = value;
    info.valueType = valueType;
    QThreadPool::globalInstance()->start(new UpdateValueTask(info));
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

QString DaqcServerHandleReceiveMessageTask::getValueType(const QJsonDocument &document)
{
    return document["data"].toObject()["valueType"].toString();
}

QVariant DaqcServerHandleReceiveMessageTask::getValue(const QJsonDocument &document)
{
    return document["data"].toObject()["value"].toVariant();
}
