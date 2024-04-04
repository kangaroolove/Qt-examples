#pragma once

#include "Packet.h"
#include <QImage>

class GetPacket : public Packet
{
public:
    GetPacket(const QJsonObject& object, const QImage& image = QImage());
    ~GetPacket();
    QByteArray toBinary() override;
protected:
    QJsonObject generateData() override;
private:
    QImage m_image;
    QJsonObject m_object;
};