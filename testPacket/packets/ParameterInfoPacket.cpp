#include "ParameterInfoPacket.h"
#include <QJsonObject>
#include <QVariantMap>
#include <QJsonDocument>
#include <QDebug>

ParameterInfoPacket::ParameterInfoPacket(const std::map<QString, QVariant> &info) :
    m_parameterInfo(info)
{
    m_packetType = PacketType::PARAMETER_INFO;
}

ParameterInfoPacket::ParameterInfoPacket(const ParameterInfoPacket &packet)
{
    m_messageId = packet.m_messageId;
    m_parameterInfo = packet.m_parameterInfo;
    m_packetType = packet.m_packetType;
}

void ParameterInfoPacket::printfSelf()
{
    qDebug()<<PACKET_TYPE<<":"<<(int)m_packetType;
    qDebug()<<MESSAGE_ID<<":"<<m_messageId;
    qDebug()<<"Parameters:";
    for (auto& item : m_parameterInfo)
        qDebug()<<item.first<<":"<<item.second;
}

ParameterInfoPacket ParameterInfoPacket::fromJson(const QByteArray &data)
{
    auto doc = QJsonDocument::fromJson(data);
    if (doc.isNull())
        return ParameterInfoPacket({});
    
    auto map = doc[Packet::DATA].toObject().toVariantMap();
    auto packet = ParameterInfoPacket(map.toStdMap());
    packet.m_messageId = Packet::getMessageIdFromJson(data);
    return packet;
}

QJsonObject ParameterInfoPacket::generateData()
{
    QVariantMap map(m_parameterInfo);
    return QJsonObject::fromVariantMap(map);
}
