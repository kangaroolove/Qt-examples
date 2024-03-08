#include "ReplyGetPacket.h"

ReplyGetPacket::ReplyGetPacket(const QString& requestType, const QString& parameter) :
    m_requestType(requestType),
    m_parameter(parameter)
{

}

ReplyGetPacket::~ReplyGetPacket()
{

}

QJsonObject ReplyGetPacket::generateData()
{
    QJsonObject object;
    object["parameter"] = m_parameter;
    object["requestType"] = m_requestType; 
    QString valueType = getValueType();
    object["valueType"] = valueType;
    if (valueType == "int")
        object["value"] = getValue().;
}
