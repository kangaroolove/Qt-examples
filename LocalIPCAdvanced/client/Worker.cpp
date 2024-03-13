#include "Worker.h"
#include <QLocalSocket>
#include <QDataStream>
#include <QJsonDocument>
#include <QImage>
#include <QJsonObject>

Worker::Worker(QObject* parent) :
    QLocalSocket(parent),
    m_in(new QDataStream(this))
{
    m_in->setVersion(QDataStream::Qt_5_12);
    connect(this, &Worker::readyRead, this, &Worker::readyToRead);
}

Worker::~Worker()
{
    delete m_in;
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
            emit requestResultInserted(clientMessageId, result);
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

bool Worker::isImagePacket(const QJsonDocument &document)
{
    return document["data"].toObject().contains("image");
}