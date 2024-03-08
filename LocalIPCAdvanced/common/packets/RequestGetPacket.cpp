#include "RequestGetPacket.h"

RequestGetPacket::RequestGetPacket(const QString& parameter) :
    m_parameter(parameter)
{

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
