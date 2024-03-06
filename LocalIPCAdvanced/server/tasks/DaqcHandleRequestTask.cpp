#include "DaqcHandleRequestTask.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

DaqcHandleRequestTask::DaqcHandleRequestTask(const QByteArray& data) :
    HandleRequestTask(data)
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

    QString requestType = getRequestType(document);
    qDebug()<<"requestType = "<< requestType;
    QString messageId = getMessageId(document);
    qDebug()<<"messageId = "<< messageId;
    QString parameter = getParameter(document);
    qDebug()<<"parameter = "<< parameter;
    //handleTask(api);
}

void DaqcHandleRequestTask::handleTask(const QString &api)
{
}

QString DaqcHandleRequestTask::getRequestType(const QJsonDocument& document)
{
    return document["data"].toObject()["requestType"].toString();
}

QString DaqcHandleRequestTask::getMessageId(const QJsonDocument &document)
{
    return document["messageId"].toString();
}

QString DaqcHandleRequestTask::getParameter(const QJsonDocument &document)
{
    return document["data"].toObject()["parameter"].toString();
}
