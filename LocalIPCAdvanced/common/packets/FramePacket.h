#pragma once

#include "Packet.h"
#include <QJsonObject>

class FramePacket : public Packet
{
public:
    FramePacket(const QJsonObject& object);
    ~FramePacket();
protected:
    QJsonObject generateData() override;
private:
    QJsonObject m_object;
};