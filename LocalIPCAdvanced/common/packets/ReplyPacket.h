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
    ~ReplyPacket();

    ReplyPacketInfo getReplyPacketInfo() const; 
protected:
    QJsonObject generateData() override;

    ReplyPacketInfo m_replyPacketInfo;
};