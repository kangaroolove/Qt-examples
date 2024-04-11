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
    m_client(client)
{
    qRegisterMetaType<QLocalSocket::LocalSocketError>("QLocalSocket::LocalSocketError");
    connect(this, &ClientWorker::readyRead, this, &ClientWorker::readyToRead);
    connect(this, QOverload<QLocalSocket::LocalSocketError>::of(&ClientWorker::error), this, [this](QLocalSocket::LocalSocketError socketError){
        qCritical()<<"socket error code"<<socketError;
        qCritical()<<errorString();
    });
}

ClientWorker::~ClientWorker()
{
}

void ClientWorker::readyToRead()
{
    if (bytesAvailable() < 0)
        return;

    //qDebug()<<"Client receive message";

    QDataStream stream(this->readAll());
    stream.setVersion(QDataStream::Qt_5_12);
    while (!stream.atEnd())
    {  
        QByteArray msg;
        QImage image;

        stream >> msg;
        stream >> image;

        QJsonParseError jsonParse;
        auto document = QJsonDocument::fromJson(msg, &jsonParse);
        if (jsonParse.error != QJsonParseError::NoError)
        {
            qCritical()<< "ClientWorker --- readyToRead ---- json parse error";
            return;
        }

        if (document.isNull())
            return;

        //qDebug()<<msg;

        auto packetType = getPacketType(document);
        if (packetType == PacketType::GET)
        {
            auto map = document["data"].toObject().toVariantMap();
            for (auto it = map.begin(); it != map.end(); ++it)
                m_client->updateResult(it.key(), it.value());

            if (!image.isNull())
                emit imageReceived(image);
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
