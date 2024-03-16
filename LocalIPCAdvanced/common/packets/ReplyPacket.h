#pragma once

#include "Packet.h"
#include <QJsonObject>
#include <QString>
#include <QVariant>

class ReplyPacketInfo
{
public:
    QString parameter;
    QString requestType;
    QString clientMessageId;
    QString valueType;
    QVariant value;
};

class ReplyPacket : public Packet
{
public:
    ReplyPacket(const ReplyPacketInfo& replyPacketInfo);
    ReplyPacket(const ReplyPacket& packet);
    ~ReplyPacket();

    ReplyPacketInfo getReplyPacketInfo() const; 
    static ReplyPacket fromJson(const QJsonObject& object);
protected:
    QJsonObject generateData() override;

    ReplyPacketInfo m_replyPacketInfo;
};