#include "ReplyPacket.h"
#include <QJsonDocument>
#include <QVariant>

ReplyPacket::ReplyPacket(const QString& parameter, const QString& requestType, const QString& clientMessageId) :
    m_clientMessageId(clientMessageId),
    m_requestType(requestType),
    m_parameter(parameter)
{

}

ReplyPacket::~ReplyPacket()
{

}

QByteArray ReplyPacket::toJson()
{
    QJsonObject object;
    object["data"] = generateData();
    object["clientMessageId"] = m_clientMessageId;
    object["messageId"] = getMessageId();
    QJsonDocument document(object);
    return document.toJson(QJsonDocument::Compact);
}

QJsonObject ReplyPacket::generateData()
{
    QJsonObject object;
    object["parameter"] = m_parameter;
    object["requestType"] = m_requestType; 
    QString valueType = getValueType();
    object["valueType"] = valueType;
    if (valueType == "int")
        object["value"] = getValue().toInt();
    else if (valueType == "bool")
        object["value"] = getValue().toBool();

    return object;
}
