#pragma once

#include "Packet.h"
#include <QImage>

class GetInfoPacket : public Packet
{
public:
    GetInfoPacket(const QJsonObject& object);
    ~GetInfoPacket();
protected:
    QJsonObject generateData() override;
private:
    QJsonObject m_object;
};