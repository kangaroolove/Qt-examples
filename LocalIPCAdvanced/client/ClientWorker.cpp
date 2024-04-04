#include "ClientWorker.h"
#include "Client.h"
#include "DaqcClientDef.h"
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
        QImage image;
        *m_in >> msg;
        *m_in >> image;

        // qDebug()<<"Client receive message";
        // qDebug()<<msg;

        auto document = QJsonDocument::fromJson(msg);
        if (document.isNull())
            return;

        auto packetType = getPacketType(document);
        if (packetType == PacketType::GET)
        {
            if (!image.isNull())
            emit imageReceived(image);

            auto map = document["data"].toObject().toVariantMap();
            for (auto it = map.begin(); it != map.end(); ++it)
                m_client->updateResult(it.key(), it.value());
        }
    }
}

void ClientWorker::sendMessage(const QByteArray &msg)
{
    qDebug()<<"Client send message";
    qDebug()<<msg;

    write(msg);
    flush();
}

QString ClientWorker::getPacketType(const QJsonDocument &document)
{
    return document["packetType"].toString();
}
