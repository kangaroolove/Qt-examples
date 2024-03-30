#include "RequestPacket.h"
#include "DaqcClientDef.h"

RequestPacket::RequestPacket()
{
    m_packetType = PacketType::REQUEST;
}

RequestPacket::RequestPacket(const QString &parameter, const QVariant &values, const QVariant &valueTypes) : 
    m_parameter(parameter),
    m_values(values),
    m_valueTypes(valueTypes)
{
    m_packetType = PacketType::REQUEST;
}

RequestPacket::~RequestPacket()
{

}

QString RequestPacket::getParameter() const
{
    return m_parameter;
}

QVariant RequestPacket::getValueTypes() const
{
    return m_valueTypes;
}

QVariant RequestPacket::getValues() const
{
    return m_values;
}
