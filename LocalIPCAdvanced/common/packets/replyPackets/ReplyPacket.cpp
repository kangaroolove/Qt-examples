#include "ReplyPacket.h"
#include <QJsonDocument>

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
    object["messageId"] = getMessageId();
    QJsonDocument document(object);
    return document.toJson(QJsonDocument::Compact);
}
