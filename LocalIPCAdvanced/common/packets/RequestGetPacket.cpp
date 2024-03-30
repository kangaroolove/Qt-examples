#include "RequestGetPacket.h"
#include "DaqcClientDef.h"
#include <QJsonArray>

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
    QVariant valueTypes = object["data"].toObject()["valueTypes"].toVariant();
    QVariant values = object["data"].toObject()["values"].toVariant();
    return RequestGetPacket(parameter, values, valueTypes, messageId);
}

QJsonObject RequestGetPacket::generateData()
{
    QJsonObject object;
    object["parameter"] = m_parameter;
    object["requestType"] = "get";

    if (!m_values.isNull())
        object["values"] = QJsonArray::fromVariantList(m_values.toList());

    if (!m_valueTypes.isNull())
        object["valueTypes"] = QJsonArray::fromStringList(m_valueTypes.toStringList());

    return object;
}
