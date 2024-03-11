#include "Client.h"
#include <QDataStream>
#include <QEventLoop>
#include <QDebug>
#include <QUuid>
#include <QThreadPool>
#include <QMutexLocker>
#include <QMutex>
#include <QJsonDocument>
#include <QJsonObject>
#include <QImage>

Client::Client(QObject* parent) : 
    QLocalSocket(parent), 
    m_in(new QDataStream(this))
{
    m_in->setVersion(QDataStream::Qt_5_12);
    connect(this, &Client::readyRead, this, &Client::readyToRead);
}

Client::~Client()
{
}

void Client::sendMessage(const QByteArray &msg)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << msg;

    this->write(data);
    this->flush();
}

void Client::insertRequestResult(const QString& messageId, const RequestResult& result)
{
    m_resultMap.insert({messageId, result});
}

RequestResult Client::getRequestResult(const QString &messageId)
{
    RequestResult result;
    auto it = m_resultMap.find(messageId);
    if (it != m_resultMap.end())
    {
        result = it->second;
        m_resultMap.erase(it);
        return result;
    }

    qCritical()<<"Cannot find the result";
    return result;
}

void Client::connectServer()
{
    this->connectToServer("Daqc");
}

bool Client::isImagePacket(const QJsonDocument& document)
{
    return document["data"].toObject().contains("image");
}

void Client::readyToRead()
{
    if (this->bytesAvailable() > 0 && !m_in->atEnd())
    {  
        QByteArray msg;
        *m_in >> msg;
        emit receiveMessage(msg);

        auto document = QJsonDocument::fromJson(msg);
        if (document.isNull())
            return;

        if (isImagePacket(document))
        {
            QByteArray imageData = document["data"].toObject()["image"].toVariant().toByteArray();
            QImage image;
            image.loadFromData(imageData);
            emit imageReceived(image);
        }
        else 
        {
            RequestResult result;
            QString clientMessageId = document["data"].toObject()["clientMessageId"].toString();
            result.value = document["data"].toObject()["value"].toVariant();
            result.valueType = document["data"].toObject()["valueType"].toString();
            insertRequestResult(clientMessageId, result);
            emit quitEventloop();
        }
    }
}
