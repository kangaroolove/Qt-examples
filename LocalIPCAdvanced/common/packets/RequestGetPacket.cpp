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

QJsonObject RequestGetPacket::generateData()
{
    QJsonObject object;
    object["parameter"] = m_parameter;
    object["requestType"] = "get";
    return object;
}
