#pragma once

#include "Packet.h"
#include <QImage>

class FramePacket : public Packet
{
public:
    FramePacket(const QImage& image);
    FramePacket(const FramePacket& framePacket);
    ~FramePacket();

    QImage getImage() const;
    static FramePacket fromJson(const QJsonObject& object);
private:
    QJsonObject generateData() override;

    QImage m_image;
};