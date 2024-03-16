#include "RequestUpdatePacket.h"
#include "StringDef.h"
#include <QJsonObject>

RequestUpdatePacket::RequestUpdatePacket(const QString& parameter, const QVariant& value, const QString& valueType) :
    m_value(value),
    m_valueType(valueType),
    m_parameter(parameter)
{
    m_packetType = REQUEST;
}

RequestUpdatePacket::RequestUpdatePacket(const RequestUpdatePacket &packet)
{
    m_value = packet.m_value;
    m_valueType = packet.m_valueType;
    m_parameter = packet.m_parameter;
}

RequestUpdatePacket::~RequestUpdatePacket()
{

}

QString RequestUpdatePacket::getParameter() const
{
    return m_parameter;
}

QString RequestUpdatePacket::getValueType() const
{
    return m_valueType;
}

QVariant RequestUpdatePacket::getValue() const
{
    return m_value;
}

RequestUpdatePacket RequestUpdatePacket::fromJson(const QJsonObject &object)
{
    QString parameter = object["data"].toObject()["parameter"].toString();
    QString valueType = object["data"].toObject()["valueType"].toString();
    QVariant value = object["data"].toObject()["value"].toVariant();
    return RequestUpdatePacket(parameter, value, valueType);
}

QJsonObject RequestUpdatePacket::generateData()
{
    QJsonObject object;
    object["parameter"] = m_parameter;
    object["requestType"] = "update";
    object["valueType"] = m_valueType;

    if (m_valueType == "int")
        object["value"] = m_value.toInt();
    else if (m_valueType == "string")
        object["value"] = m_value.toString();
    else if (m_valueType == "bool")
        object["value"] = m_value.toBool();
    else if (m_valueType == "double")
        object["value"] = m_value.toDouble();
    return object;
}
