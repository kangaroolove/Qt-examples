#include "RequestGetPacket.h"
#include "StringDef.h"

RequestGetPacket::RequestGetPacket(const RequestGetPacket &packet)
{
    m_parameter = packet.m_parameter;
}

RequestGetPacket::RequestGetPacket(const QString &parameter, const QString &messageId) :
    m_parameter(parameter)
{
    m_packetType = PacketType::REQUEST;
    if (!messageId.isNull())
        m_messageId = messageId;
}

RequestGetPacket::~RequestGetPacket()
{

}

QString RequestGetPacket::getParameter() const
{
    return m_parameter;
}

RequestGetPacket RequestGetPacket::fromJson(const QJsonObject &object)
{
    QString parameter = object["data"].toObject()["parameter"].toString();
    QString messageId = object["messageId"].toString();
    return RequestGetPacket(parameter, messageId);
}

QJsonObject RequestGetPacket::generateData()
{
    QJsonObject object;
    object["parameter"] = m_parameter;
    object["requestType"] = "get";
    return object;
}
