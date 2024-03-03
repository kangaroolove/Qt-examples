#pragma once

#include "Packet.h"

class ReplyPacket : public Packet
{
public:
    ReplyPacket();
    ~ReplyPacket();
    QByteArray toJson() override;
private:

};