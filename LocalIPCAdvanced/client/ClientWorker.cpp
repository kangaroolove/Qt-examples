#include "ClientWorker.h"
#include "Client.h"
#include "DaqcClientDef.h"
#include <QLocalSocket>
#include <QDataStream>
#include <QJsonDocument>
#include <QImage>
#include <QJsonObject>

const int ClientWorker::m_COMMUNICATION_JAM_THRESHOLD = 400000;

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
    // In a RTC application, handling message is slower than receiving message sometimes.
    // So we need to use while rather than if here
    while (bytesAvailable() > 0 && !m_in->atEnd())
    {  
        if (bytesAvailable() > m_COMMUNICATION_JAM_THRESHOLD)
            qCritical()<<"There is a communication jam in ClientWorker";

        QByteArray msg;
        QImage image;

        *m_in >> msg;
        *m_in >> image;

        qDebug()<<"Client receive message";
        qDebug()<<msg;

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
    // qDebug()<<"Client send message";
    // qDebug()<<msg;

    write(msg);
    flush();
}

QString ClientWorker::getPacketType(const QJsonDocument &document)
{
    return document["packetType"].toString();
}
