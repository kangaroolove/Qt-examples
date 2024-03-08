#include "DaqcServerHandleReceiveMessageTask.h"
#include "SendTask.h"
#include "ReplyPacket.h"
#include "ReplyGetPacket.h"
#include "Server.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QUuid>
#include <QThreadPool>

DaqcServerHandleReceiveMessageTask::DaqcServerHandleReceiveMessageTask(Server* server, const QByteArray& data) :
    HandleReceiveMessageTask(data),
    m_server(server)
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
    qDebug()<<"clientMessageId = "<< clientMessageId;

    if (parameter == "test" && requestType == "get")
    {
        QThreadPool::globalInstance()->start(new SendTask(m_server, new ReplyGetPacket( clientMessageId)));
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
