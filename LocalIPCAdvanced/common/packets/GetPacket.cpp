#include "GetPacket.h"

GetPacket::GetPacket(const QJsonObject& object, const QImage& image) : 
    m_image(image),
    m_object(object)
{

}

GetPacket::~GetPacket()
{

}

QByteArray GetPacket::toBinary()
{ 
    QByteArray data = Packet::toBinary();
    if (!m_image.isNull())
    {
        QDataStream stream(&data, QIODevice::WriteOnly | QIODevice::Append);
        stream.setVersion(QDataStream::Qt_5_12);
        stream << m_image;
    }

    return data;
}

QJsonObject GetPacket::generateData()
{   
    return m_object;
}
