#include "FramePacket.h"
#include <QDebug>

const QString FramePacket::IMAGE_CHANNEL = "ImageChannel";

FramePacket::FramePacket(const QImage& image, const ImageChannel& channel) :
    m_imageChannel(channel),
    m_image(image)
{
    m_packetType = PacketType::FRAME;
}

QByteArray FramePacket::toBinary()
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_5_12);
    stream << toJson();
    stream << m_image;
    return data;
}

void FramePacket::printfSelf()
{
    qDebug()<<PACKET_TYPE<<":"<<(int)m_packetType;
    qDebug()<<IMAGE_CHANNEL<<":"<<(int)m_imageChannel;
    qDebug()<<MESSAGE_ID<<":"<<m_messageId;
}

QImage FramePacket::getImage() const
{
    return m_image;
}

ImageChannel FramePacket::getImageChannel() const
{
    return m_imageChannel;
}

QJsonObject FramePacket::generateData()
{
    QJsonObject object;
    object[IMAGE_CHANNEL] = (int)m_imageChannel;
    return object;
}
