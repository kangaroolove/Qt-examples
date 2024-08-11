#include "Packet.h"
#include <QJsonDocument>
#include <QUuid>
#include <QDataStream>

const QString Packet::PACKET_TYPE = "packetType";
const QString Packet::DATA = "data";
const QString Packet::MESSAGE_ID = "messageId";

Packet::Packet(QObject* parent) :
    QObject(parent),
    m_packetType(PacketType::UNKNOWN),
    m_messageId(generateMessageId())
{
}

QByteArray Packet::toJson()
{
    QJsonObject object;
    object[DATA] = generateData();
    object[MESSAGE_ID] = getMessageId();
    object[PACKET_TYPE] = (int)m_packetType;
    QJsonDocument document(object);
    return document.toJson(QJsonDocument::Compact);
}

QString Packet::getMessageId() const
{
    return m_messageId;
}

QByteArray Packet::toBinary()
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_5_12);
    stream << toJson();
    return data;
}

PacketType Packet::getType() const
{
    return m_packetType;
}

PacketType Packet::getTypeFromBinaryData(const QByteArray &data)
{
    auto doc = QJsonDocument::fromBinaryData(data);
    if (doc.isNull())
        return PacketType::UNKNOWN;
    
    return PacketType(doc[PACKET_TYPE].toInt());
}

PacketType Packet::getTypeFromJson(const QByteArray &data)
{
    auto doc = QJsonDocument::fromJson(data);
    if (doc.isNull())
        return PacketType::UNKNOWN;
    
    return PacketType(doc[PACKET_TYPE].toInt());
}

QString Packet::getMessageIdFromBinaryData(const QByteArray &data)
{
    auto doc = QJsonDocument::fromBinaryData(data);
    if (doc.isNull())
        return QString();
    
    return doc[PACKET_TYPE].toString();
}

QString Packet::getMessageIdFromJson(const QByteArray &data)
{
    auto doc = QJsonDocument::fromJson(data);
    if (doc.isNull())
        return QString();
    
    return doc[PACKET_TYPE].toString();
}

void Packet::setMessageId(const QString &messageId)
{
    m_messageId = messageId;
}

QString Packet::generateMessageId()
{
    return QUuid::createUuid().toString();
}
