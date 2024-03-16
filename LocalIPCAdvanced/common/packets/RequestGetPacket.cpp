#include "RequestGetPacket.h"
#include "StringDef.h"

RequestGetPacket::RequestGetPacket(const QString& parameter) :
    m_parameter(parameter)
{
    m_packetType = REQUEST;
}

RequestGetPacket::RequestGetPacket(const RequestGetPacket &packet)
{
    m_parameter = packet.m_parameter;
}

RequestGetPacket::~RequestGetPacket()
{

}

QString RequestGetPacket::getParameter() const
{
    return m_parameter;
}

RequestGetPacket RequestGetPacket::fromJson(const QJsonObject &object)
{
    QString parameter = object["data"].toObject()["parameter"].toString();
    return RequestGetPacket(parameter);
}

QJsonObject RequestGetPacket::generateData()
{
    QJsonObject object;
    object["parameter"] = m_parameter;
    object["requestType"] = "get";
    return object;
}
