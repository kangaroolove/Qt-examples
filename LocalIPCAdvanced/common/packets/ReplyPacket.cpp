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
    info.values = object["data"].toObject()["values"].toVariant();
    info.valueTypes = object["data"].toObject()["valueTypes"].toVariant();
    return ReplyPacket(info);
}

QJsonObject ReplyPacket::generateData()
{
    QJsonObject object;
    object["parameter"] = m_replyPacketInfo.parameter;
    object["requestType"] = m_replyPacketInfo.requestType; 
    object["clientMessageId"] = m_replyPacketInfo.clientMessageId;
    object["valueTypes"] = QJsonArray::fromStringList(m_replyPacketInfo.valueTypes.toStringList());
    object["values"] = QJsonArray::fromVariantList(m_replyPacketInfo.values.toList());
    return object;
}
