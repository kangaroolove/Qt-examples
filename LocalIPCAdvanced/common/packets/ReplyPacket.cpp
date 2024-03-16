#include "ReplyPacket.h"
#include "StringDef.h"
#include <QJsonDocument>
#include <QVariant>

ReplyPacket::ReplyPacket(const ReplyPacketInfo& replyPacketInfo) :
    m_replyPacketInfo(replyPacketInfo)
{
    m_packetType = REPLY;
}

ReplyPacket::ReplyPacket(const ReplyPacket &packet)
{
    m_replyPacketInfo = packet.m_replyPacketInfo;
}

ReplyPacket::~ReplyPacket()
{

}

ReplyPacketInfo ReplyPacket::getReplyPacketInfo() const
{
    return m_replyPacketInfo;
}

ReplyPacket ReplyPacket::fromJson(const QJsonObject& object)
{
    ReplyPacketInfo info;
    info.clientMessageId = object["data"].toObject()["clientMessageId"].toString();
    info.parameter = object["data"].toObject()["parameter"].toString();
    info.requestType = object["data"].toObject()["requestType"].toString();
    info.value = object["data"].toObject()["value"].toVariant();
    info.valueType = object["data"].toObject()["requestType"].toString();

    return ReplyPacket(info);
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
