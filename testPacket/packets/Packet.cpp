#include "Packet.h"
#include <QJsonDocument>
#include <QUuid>
#include <QDataStream>

Packet::Packet(QObject* parent) :
    QObject(parent),
    m_packetType(PacketType::UNKNOWN)
{
    generateMessageId();
}

QByteArray Packet::toJson()
{
    QJsonObject object;
    object["data"] = generateData();
    object["messageId"] = getMessageId();
    object["packetType"] = (int)m_packetType;
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

void Packet::generateMessageId()
{
    m_messageId = QUuid::createUuid().toString();
}
