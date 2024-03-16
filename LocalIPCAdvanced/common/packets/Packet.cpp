#include "Packet.h"
#include "StringDef.h"
#include <QJsonDocument>
#include <QUuid>

Packet::Packet(QObject* parent) :
    QObject(parent),
    m_packetType(UNKNOWN_PACKET)
{
    generateMessageId();
}

Packet::~Packet()
{

}

QByteArray Packet::toJson()
{
    QJsonObject object;
    object["data"] = generateData();
    object["messageId"] = getMessageId();
    object["packetType"] = m_packetType;
    QJsonDocument document(object);
    return document.toJson(QJsonDocument::Compact);
}

QString Packet::getMessageId()
{
    return m_messageId;
}

void Packet::generateMessageId()
{
    m_messageId = QUuid::createUuid().toString();
}
