#pragma once

#include "Packet.h"

class CommandPacket : public Packet
{
public:
    CommandPacket(const QString& command);
    ~CommandPacket();
    
    QString getCommand() const;
protected:
    QJsonObject generateData() override;
private:
    QString m_command;
};