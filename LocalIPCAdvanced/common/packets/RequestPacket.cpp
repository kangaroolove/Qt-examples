#include "RequestPacket.h"
#include <QJsonObject>
#include <QJsonDocument>

RequestPacket::RequestPacket()
{

}

RequestPacket::~RequestPacket()
{

}

QByteArray RequestPacket::toJson()
{
    QJsonObject object;
    object["messageId"] = getMessageId();
    object["data"] = generateData();
    QJsonDocument document(object);
    return document.toJson(QJsonDocument::Compact);
}
