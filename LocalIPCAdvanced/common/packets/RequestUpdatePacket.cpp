#include "RequestUpdatePacket.h"
#include "StringDef.h"
#include <QJsonObject>
#include <QJsonArray>

RequestUpdatePacket::RequestUpdatePacket(const QString& parameter, const QVariant& values, const QVariant& valueTypes) :
    m_values(values),
    m_valueTypes(valueTypes),
    m_parameter(parameter)
{
    m_packetType = PacketType::REQUEST;
}

RequestUpdatePacket::RequestUpdatePacket(const RequestUpdatePacket &packet)
{
    m_values = packet.m_values;
    m_valueTypes = packet.m_valueTypes;
    m_parameter = packet.m_parameter;
}

RequestUpdatePacket::~RequestUpdatePacket()
{

}

QString RequestUpdatePacket::getParameter() const
{
    return m_parameter;
}

QVariant RequestUpdatePacket::getValueTypes() const
{
    return m_valueTypes;
}

QVariant RequestUpdatePacket::getValues() const
{
    return m_values;
}

RequestUpdatePacket RequestUpdatePacket::fromJson(const QJsonObject &object)
{
    QString parameter = object["data"].toObject()["parameter"].toString();
    QVariant valueTypes = object["data"].toObject()["valueTypes"].toVariant();
    QVariant values = object["data"].toObject()["values"].toVariant();
    return RequestUpdatePacket(parameter, values, valueTypes);
}

QJsonObject RequestUpdatePacket::generateData()
{
    QJsonObject object;
    object["parameter"] = m_parameter;
    object["requestType"] = "update";
    object["valueTypes"] = QJsonArray::fromStringList(m_valueTypes.toStringList());
    object["values"] = QJsonArray::fromVariantList(m_values.toList());
    return object;
}
