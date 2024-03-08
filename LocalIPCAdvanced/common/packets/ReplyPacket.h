#pragma once

#include "Packet.h"
#include <QJsonObject>
#include <QString>
class ReplyPacket : public Packet
{
public:
    ReplyPacket(const QString& clientMessageId);
    ~ReplyPacket();
    QByteArray toJson() override;
protected:
    QString m_clientMessageId;
};

class TestGetApiPacket : public ReplyPacket
{
public:
    TestGetApiPacket(const QString& clientMessageId);
    ~TestGetApiPacket();
    QJsonObject generateData() override;
};