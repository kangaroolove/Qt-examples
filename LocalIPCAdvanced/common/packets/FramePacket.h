#pragma once

#include "Packet.h"
#include <QImage>

class FramePacket : public Packet
{
public:
    FramePacket(const QImage& image);
    ~FramePacket();

    QImage getImage() const;
private:
    QJsonObject generateData() override;

    QImage m_image;
};