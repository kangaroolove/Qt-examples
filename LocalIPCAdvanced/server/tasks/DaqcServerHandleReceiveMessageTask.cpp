#include "DaqcServerHandleReceiveMessageTask.h"
#include "SendTask.h"
#include "Server.h"
#include "UpdateValueTask.h"
#include "RequestGetPacket.h"
#include "DaqcClientDef.h"
#include "RequestUpdatePacket.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QUuid>
#include <QThreadPool>

DaqcServerHandleReceiveMessageTask::DaqcServerHandleReceiveMessageTask(Server* server, Daqc* daqc, const QByteArray& data) :
    HandleReceiveMessageTask(data),
    m_server(server),
    m_daqc(daqc)
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
    if (packetType == PacketType::REQUEST)
    {
        auto requestType = getRequestType(document);
        if (requestType == "update")
        {
            auto packet = RequestUpdatePacket::fromJson(document.object());
            handleUpdateRequest(packet.getParameter(), packet.getValueTypes(), packet.getValues());
        }
    }
}

void DaqcServerHandleReceiveMessageTask::handleUpdateRequest(const QString &parameter, const QVariant &valueTypes, const QVariant &values)
{
    UpdateValueInfo info;
    info.parameter = parameter;
    info.values = values;
    info.valueTypes = valueTypes;
    QThreadPool::globalInstance()->start(new UpdateValueTask(info, m_daqc));
}

QString DaqcServerHandleReceiveMessageTask::getRequestType(const QJsonDocument &document) const
{
    return document["data"].toObject()["requestType"].toString();
}

QString DaqcServerHandleReceiveMessageTask::getPacketType(const QJsonDocument &document) const
{
    return document["packetType"].toString();
}
