#include "ReplyPacket.h"
#include <QJsonDocument>
#include <QVariant>

ReplyPacket::ReplyPacket(const ReplyPacketInfo& replyPacketInfo) :
    m_replyPacketInfo(replyPacketInfo)
{

}

ReplyPacket::~ReplyPacket()
{

}

QByteArray ReplyPacket::toJson()
{
    QJsonObject object;
    object["data"] = generateData();

    
    object["messageId"] = getMessageId();
    QJsonDocument document(object);
    return document.toJson(QJsonDocument::Compact);
}

QJsonObject ReplyPacket::generateData()
{
    QJsonObject object;
    object["parameter"] = m_replyPacketInfo.parameter;
    object["requestType"] = m_replyPacketInfo.requestType; 
    object["clientMessageId"] = m_replyPacketInfo.clientMessageId;
    object["valueType"] = m_replyPacketInfo.valueType;

    if (m_replyPacketInfo.valueType == "int")
        object["value"] = m_replyPacketInfo.value.toInt();
    else if (m_replyPacketInfo.valueType == "string")
        object["value"] = m_replyPacketInfo.value.toString();
    else if (m_replyPacketInfo.valueType == "bool")
        object["value"] = m_replyPacketInfo.value.toBool();
    else if (m_replyPacketInfo.valueType == "double")
        object["value"] = m_replyPacketInfo.value.toDouble();

    return object;
}
