#pragma once

#include "Packet.h"

class CommandPacket : public Packet
{
public:
    CommandPacket(const QString& command);
    CommandPacket(const CommandPacket& packet);
    ~CommandPacket();
    
    QString getCommand() const;
    static CommandPacket fromJson(const QJsonObject& object);
protected:
    QJsonObject generateData() override;
private:
    QString m_command;
};