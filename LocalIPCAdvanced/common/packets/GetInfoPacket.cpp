#include "GetInfoPacket.h"
#include "DaqcClientDef.h"

GetInfoPacket::GetInfoPacket(const QJsonObject& object) : 
    m_object(object)
{
    m_packetType = PacketType::GET_INFO;
}

GetInfoPacket::~GetInfoPacket()
{

}

QJsonObject GetInfoPacket::generateData()
{   
    return m_object;
}
