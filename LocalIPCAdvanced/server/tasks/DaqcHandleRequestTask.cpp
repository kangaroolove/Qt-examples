#include "DaqcHandleRequestTask.h"
#include "SendTask.h"
#include "ReplyPacket.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QUuid>
#include <QThreadPool>

DaqcHandleRequestTask::DaqcHandleRequestTask(Server* server, const QByteArray& data) :
    HandleRequestTask(data),
    m_server(server)
{

}

DaqcHandleRequestTask::~DaqcHandleRequestTask()
{

}

void DaqcHandleRequestTask::analyzeJson(const QByteArray &data)
{
    auto document = QJsonDocument::fromJson(data);
    if (document.isNull())
        return;

    handleTask(getParameter(document), getRequestType(document), getClientMessageId(document));
}

void DaqcHandleRequestTask::handleTask(const QString &parameter, const QString &requestType, const QString &clientMessageId)
{
    qDebug()<<"parameter = "<< parameter;
    qDebug()<<"requestType = "<< requestType;
    qDebug()<<"clientMessageId = "<< clientMessageId;

    if (parameter == "testApi")
    {
        QThreadPool::globalInstance()->start(new SendTask(m_server, new TestGetApiPacket(clientMessageId)));
    }
}

QString DaqcHandleRequestTask::getRequestType(const QJsonDocument &document)
{
    return document["data"].toObject()["requestType"].toString();
}

QString DaqcHandleRequestTask::getClientMessageId(const QJsonDocument &document)
{
    return document["messageId"].toString();
}

QString DaqcHandleRequestTask::getParameter(const QJsonDocument &document)
{
    return document["data"].toObject()["parameter"].toString();
}
