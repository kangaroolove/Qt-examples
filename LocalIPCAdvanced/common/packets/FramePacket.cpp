#include "FramePacket.h"

FramePacket::FramePacket(const QImage& image) :
    m_image(image)
{

}

FramePacket::~FramePacket()
{

}

QByteArray FramePacket::toJson()
{
    QJsonObject rootObject;

    object["data"] = 
    object["messageId"] = getMessageId();

}

QJsonObject FramePacket::generateData()
{
    QJsonObject object;
    object
    return object;
}
