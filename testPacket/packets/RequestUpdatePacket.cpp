#include "RequestUpdatePacket.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

RequestUpdatePacket::RequestUpdatePacket(const QString& parameter, const QVariant& values, const QVariant& valueTypes)
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

RequestUpdatePacket RequestUpdatePacket::fromBinaryData(const QByteArray &data)
{
    auto doc = QJsonDocument::fromBinaryData(data);
    if (doc.isNull())
        return RequestUpdatePacket(QString(), QVariant(), QVariant());

    QString parameter = doc["data"].toObject()["parameter"].toString();
    QVariant valueTypes = doc["data"].toObject()["valueTypes"].toVariant();
    QVariant values = doc["data"].toObject()["values"].toVariant();
    auto packet = RequestUpdatePacket(parameter, values, valueTypes);
    packet.m_messageId = Packet::getMessageIdFromBinaryData(data);
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

QJsonObject RequestUpdatePacket::generateData()
{
    QJsonObject object;
    object["parameter"] = m_parameter;
    object["valueTypes"] = QJsonArray::fromStringList(m_valueTypes.toStringList());
    object["values"] = QJsonArray::fromVariantList(m_values.toList());
    return object;
}
