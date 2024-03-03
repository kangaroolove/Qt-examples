#pragma once

#include "Packet.h"

class FramePacket : public Packet
{
public:
    FramePacket();
    ~FramePacket();
    QByteArray toJson() override;
private:

};