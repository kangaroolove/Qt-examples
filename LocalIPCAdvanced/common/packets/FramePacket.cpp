#include "FramePacket.h"
#include "StringDef.h"
#include <QBuffer>
#include <QJsonValue>
#include <QVariant>

FramePacket::FramePacket(const QImage& image) :
    m_image(image)
{
    m_packetType = FRAME;
}

FramePacket::~FramePacket()
{

}

QImage FramePacket::getImage() const
{
    return m_image;
}

QJsonObject FramePacket::generateData()
{
    QJsonObject object;
    QByteArray data;
    QBuffer buffer(&data);
    m_image.save(&buffer, "PNG");
    object["image"] = QJsonValue::fromVariant(buffer.data().toBase64());
    return object;
}
