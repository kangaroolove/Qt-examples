#include "FramePacket.h"
#include <QDebug>
#include <QJsonDocument>

const QString FramePacket::IMAGE_CHANNEL = "ImageChannel";

FramePacket::FramePacket(const QImage& image, const ImageChannel& channel) :
    m_imageChannel(channel),
    m_image(image)
{
    m_packetType = PacketType::FRAME;
}

FramePacket::FramePacket(const FramePacket &packet)
{
    m_imageChannel = packet.m_imageChannel;
    m_image = packet.m_image;
    m_messageId = packet.m_messageId;
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

FramePacket FramePacket::fromJson(const QByteArray &data)
{
    auto doc = QJsonDocument::fromJson(data);
    if (doc.isNull())
        return FramePacket(QImage(), ImageChannel::DEFAULT_OR_DUAL_LINEAR);

    ImageChannel channel = (ImageChannel)doc[Packet::DATA].toObject()[IMAGE_CHANNEL].toInt();
    auto packet = FramePacket(QImage(), channel);
    packet.m_messageId = Packet::getMessageIdFromJson(data);
    return packet;
}

QJsonObject FramePacket::generateData()
{
    QJsonObject object;
    object[IMAGE_CHANNEL] = (int)m_imageChannel;
    return object;
}
