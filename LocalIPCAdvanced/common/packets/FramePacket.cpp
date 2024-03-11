#include "FramePacket.h"
#include <QBuffer>
#include <QJsonValue>
#include <QVariant>

FramePacket::FramePacket(const QImage& image) :
    m_image(image)
{

}

FramePacket::~FramePacket()
{

}

QJsonObject FramePacket::generateData()
{
    QJsonObject object;
    QByteArray data;
    QBuffer buffer(&data);
    m_image.save(&buffer, "PNG");
    object["image"] = QJsonValue::fromVariant(data);
    return object;
}
