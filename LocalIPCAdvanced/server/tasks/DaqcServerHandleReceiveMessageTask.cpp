#include "DaqcServerHandleReceiveMessageTask.h"
#include "SendTask.h"
#include "Server.h"
#include "UpdateValueTask.h"
#include "GetValueTask.h"
#include "RequestGetPacket.h"
#include "StringDef.h"
#include "RequestUpdatePacket.h"
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

    QString packetType = getPacketType(document);
    if (packetType == REQUEST)
    {
        auto requestType = getRequestType(document);
        if (requestType == "get")
        {
            auto packet = RequestGetPacket::fromJson(document.object());
            QThreadPool::globalInstance()->start(new GetValueTask(m_server, packet.getParameter(), packet.getMessageId()));
        }
        else if (requestType == "update")
        {
            auto packet = RequestUpdatePacket::fromJson(document.object());
            handleUpdateRequest(packet.getParameter(), packet.getValueType(), packet.getValue());
        }
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

QString DaqcServerHandleReceiveMessageTask::getRequestType(const QJsonDocument &document) const
{
    return document["data"].toObject()["requestType"].toString();
}

QString DaqcServerHandleReceiveMessageTask::getPacketType(const QJsonDocument &document) const
{
    return document["packetType"].toString();
}
