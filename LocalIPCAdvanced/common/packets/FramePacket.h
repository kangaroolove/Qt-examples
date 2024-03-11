#pragma once

#include "Packet.h"

class FramePacket : public Packet
{
public:
    FramePacket(const QImage& image);
    ~FramePacket();
private:
    QJsonObject generateData() override;

    QImage m_image;
};