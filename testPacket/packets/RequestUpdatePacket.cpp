#include "RequestUpdatePacket.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

const QString RequestUpdatePacket::PARAMETER = "parameter";
const QString RequestUpdatePacket::VALUE_TYPES = "valueTypes";
const QString RequestUpdatePacket::VALUES = "values";

RequestUpdatePacket::RequestUpdatePacket(const QString& parameter, const QVariant& values, const QVariant& valueTypes) :
    m_parameter(parameter),
    m_values(values),
    m_valueTypes(valueTypes)
{
    m_packetType = PacketType::REQUEST_UPDATE;
}

RequestUpdatePacket::RequestUpdatePacket(const RequestUpdatePacket &packet)
{
    m_packetType = packet.m_packetType;
    m_parameter = packet.m_parameter;
    m_values = packet.m_values;
    m_valueTypes = packet.m_valueTypes;
    m_messageId = packet.m_messageId;
}

RequestUpdatePacket RequestUpdatePacket::fromJson(const QByteArray &data)
{
    auto doc = QJsonDocument::fromJson(data);
    if (doc.isNull())
        return RequestUpdatePacket(QString(), QVariant(), QVariant());

    QString parameter = doc[Packet::DATA].toObject()[PARAMETER].toString();
    QStringList valueTypes = doc[Packet::DATA].toObject()[VALUE_TYPES].toVariant().toStringList();
    QVariant values = doc[Packet::DATA].toObject()[VALUES].toVariant().toList();
    auto packet = RequestUpdatePacket(parameter, values, valueTypes);
    packet.m_messageId = Packet::getMessageIdFromJson(data);
    return packet;
}

QString RequestUpdatePacket::getParameter() const
{
    return m_parameter;
}

QVariant RequestUpdatePacket::getValueTypes() const
{
    return m_valueTypes;
}

QVariant RequestUpdatePacket::getValues() const
{
    return m_values;
}

void RequestUpdatePacket::printfSelf()
{
    qDebug()<<PACKET_TYPE<<":"<<(int)m_packetType;
    qDebug()<<PARAMETER<<":"<<m_parameter;
    qDebug()<<VALUE_TYPES<<":"<<m_valueTypes;
    qDebug()<<VALUES<<":"<<m_values;
    qDebug()<<MESSAGE_ID<<":"<<m_messageId;
}

QJsonObject RequestUpdatePacket::generateData()
{
    QJsonObject object;
    object[PARAMETER] = m_parameter;
    object[VALUE_TYPES] = QJsonArray::fromStringList(m_valueTypes.toStringList());
    object[VALUES] = QJsonArray::fromVariantList(m_values.toList());
    return object;
}
