#include "RequestGetPacket.h"
#include "StringDef.h"

RequestGetPacket::RequestGetPacket(const RequestGetPacket &packet)
{
    m_parameter = packet.m_parameter;
    m_values = packet.m_values;
    m_valueTypes = packet.m_valueTypes;
}

RequestGetPacket::RequestGetPacket(const QString& parameter, const QVariant& values, const QVariant& valueTypes, const QString& messageId) :
    RequestPacket(parameter, values, valueTypes)
{
    if (!messageId.isNull())
        m_messageId = messageId;
}

RequestGetPacket::~RequestGetPacket()
{

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
