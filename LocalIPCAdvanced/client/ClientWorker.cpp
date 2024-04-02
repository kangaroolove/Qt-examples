#include "ClientWorker.h"
#include "Client.h"
#include "DaqcClientDef.h"
#include "FramePacket.h"
#include "ReplyPacket.h"
#include <QLocalSocket>
#include <QDataStream>
#include <QJsonDocument>
#include <QImage>
#include <QJsonObject>

ClientWorker::ClientWorker(Client* client, QObject* parent) :
    QLocalSocket(parent),
    m_client(client),
    m_in(new QDataStream(this))
{
    m_in->setVersion(QDataStream::Qt_5_12);
    connect(this, &ClientWorker::readyRead, this, &ClientWorker::readyToRead);
}

ClientWorker::~ClientWorker()
{
}

void ClientWorker::readyToRead()
{
    if (bytesAvailable() > 0 && !m_in->atEnd())
    {  
        QByteArray msg;
        *m_in >> msg;

        //qDebug()<<"Client receive message";
        //qDebug()<<msg;

        auto document = QJsonDocument::fromJson(msg);
        if (document.isNull())
            return;

        auto packetType = getPacketType(document);
        if (packetType == PacketType::FRAME)
        {
            auto framePacket = FramePacket::fromJson(document.object());
            emit imageReceived(framePacket.getImage());
        }
        else if (packetType == PacketType::REPLY)
        {
            auto replyPacket = ReplyPacket::fromJson(document.object());
            auto info = replyPacket.getReplyPacketInfo();
            m_client->insertRequestResult(info.clientMessageId, RequestResult(info.valueType, info.value));
            emit eventLoopQuitted();
        }
    }
}

void ClientWorker::sendMessage(const QByteArray &msg)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << msg;

    qDebug()<<"Client send message";
    //qDebug()<<msg;

    write(data);
    flush();
}

QString ClientWorker::getPacketType(const QJsonDocument &document)
{
    return document["packetType"].toString();
}
