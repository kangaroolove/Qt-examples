#pragma once

class Packet;

#include <QString>
#include <QObject>

class PacketFactory : QObject
{
    Q_OBJECT
public:
    PacketFactory(QObject* parent = nullptr);
    ~PacketFactory();
    Packet* createReplyPacket(const QString& parameter, const QString& clientMessageId);
};