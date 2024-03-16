#include "RequestGetPacket.h"
#include "StringDef.h"

RequestGetPacket::RequestGetPacket(const QString& parameter) :
    m_parameter(parameter)
{
    m_packetType = REQUEST;
}

RequestGetPacket::~RequestGetPacket()
{

}

QString RequestGetPacket::getParameter() const
{
    return m_parameter;
}

QJsonObject RequestGetPacket::generateData()
{
    QJsonObject object;
    object["parameter"] = m_parameter;
    object["requestType"] = "get";
    return object;
}
