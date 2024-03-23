#include "ReplyPacket.h"
#include "StringDef.h"
#include <QJsonDocument>
#include <QVariant>
#include <QJsonArray>

ReplyPacket::ReplyPacket(const ReplyPacketInfo& replyPacketInfo) :
    m_replyPacketInfo(replyPacketInfo)
{
    m_packetType = PacketType::REPLY;
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
    info.valueType = object["data"].toObject()["valueType"].toVariant();
    return ReplyPacket(info);
}

QJsonObject ReplyPacket::generateData()
{
    QJsonObject object;
    object["parameter"] = m_replyPacketInfo.parameter;
    object["requestType"] = m_replyPacketInfo.requestType; 
    object["clientMessageId"] = m_replyPacketInfo.clientMessageId;
    object["valueType"] = QJsonValue::fromVariant(m_replyPacketInfo.valueType);
    object["value"] = QJsonValue::fromVariant(m_replyPacketInfo.value);
    return object;
}
