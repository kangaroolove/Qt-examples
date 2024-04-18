#include "FramePacket.h"
#include "DaqcClientDef.h"

FramePacket::FramePacket()
{
    m_packetType = PacketType::FRAME;
}

FramePacket::~FramePacket()
{

}

QJsonObject FramePacket::generateData()
{
    return QJsonObject();
}
