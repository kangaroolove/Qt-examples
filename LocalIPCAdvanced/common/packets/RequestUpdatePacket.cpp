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

RequestUpdatePacket::~RequestUpdatePacket()
{

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
