#pragma once

#include "Packet.h"

class FramePacket : public Packet
{
public:
    FramePacket();
    ~FramePacket();
protected:
    QJsonObject generateData() override;
private:

};