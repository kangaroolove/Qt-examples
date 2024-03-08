#include "ReplyPacket.h"
#include <QJsonDocument>
#include <QUuid>

ReplyPacket::ReplyPacket(const QString& clientMessageId) :
    m_clientMessageId(clientMessageId)
{

}

ReplyPacket::~ReplyPacket()
{

}

QByteArray ReplyPacket::toJson()
{
    QJsonObject object;
    object["data"] = generateData();
    object["clientMessageId"] = m_clientMessageId;
    object["messageId"] = QUuid::createUuid().toString();
    QJsonDocument document(object);
    return document.toJson(QJsonDocument::Compact);
}

TestGetApiPacket::TestGetApiPacket(const QString &clientMessageId) :
    ReplyPacket(clientMessageId)
{
}

TestGetApiPacket::~TestGetApiPacket()
{
}

QJsonObject TestGetApiPacket::generateData()
{
    QJsonObject object;
    object["value"] = 20;
    object["valueType"] = "int";
    return object;
}
