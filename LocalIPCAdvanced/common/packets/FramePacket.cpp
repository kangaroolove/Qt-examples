#include "FramePacket.h"
#include "DaqcClientDef.h"

FramePacket::FramePacket(const QJsonObject& object) :
    m_object(object)
{
    m_packetType = PacketType::FRAME;
}

FramePacket::~FramePacket()
{

}

QJsonObject FramePacket::generateData()
{
    return m_object;
}
