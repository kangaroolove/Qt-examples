#include "Worker.h"
#include "Client.h"
#include "StringDef.h"
#include "FramePacket.h"
#include "ReplyPacket.h"
#include <QLocalSocket>
#include <QDataStream>
#include <QJsonDocument>
#include <QImage>
#include <QJsonObject>

Worker::Worker(Client* client, QObject* parent) :
    QLocalSocket(parent),
    m_client(client),
    m_in(new QDataStream(this))
{
    m_in->setVersion(QDataStream::Qt_5_12);
    connect(this, &Worker::readyRead, this, &Worker::readyToRead);
}

Worker::~Worker()
{
}

void Worker::readyToRead()
{
    if (bytesAvailable() > 0 && !m_in->atEnd())
    {  
        QByteArray msg;
        *m_in >> msg;

        emit messageReceived(msg);

        auto document = QJsonDocument::fromJson(msg);
        if (document.isNull())
            return;

        auto packetType = getPacketType(document);
        if (packetType == FRAME)
        {
            auto framePacket = FramePacket::fromJson(document.object());
            emit imageReceived(framePacket.getImage());
        }
        else if (packetType == REPLY)
        {
            auto replyPacket = ReplyPacket::fromJson(document.object());
            auto info = replyPacket.getReplyPacketInfo();
            m_client->insertRequestResult(info.clientMessageId, RequestResult(info.valueType, info.value));
            emit eventLoopQuitted();
        }
    }
}

void Worker::sendMessage(const QByteArray &msg)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << msg;

    write(data);
    flush();
}

QString Worker::getPacketType(const QJsonDocument &document)
{
    return document["packetType"].toString();
}
