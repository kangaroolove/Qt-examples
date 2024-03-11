#include "Packet.h"
#include <QJsonDocument>
#include <QUuid>

Packet::Packet(QObject* parent) :
    QObject(parent)
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
