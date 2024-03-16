#pragma once

#include "Packet.h"

class CommandPacket : public Packet
{
public:
    CommandPacket(const QString& command);
    ~CommandPacket();
protected:
    QJsonObject generateData() override;
private:
    QString m_command;
};