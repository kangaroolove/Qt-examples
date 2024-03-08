#pragma once

#include "Packet.h"

class RequestPacket : public Packet
{
public:
    RequestPacket();
    ~RequestPacket();
    QByteArray toJson() override;

};