#include "Client.h"
#include <QDataStream>
#include <QDebug>
#include <QImage>

Client::Client(QObject* parent)
    : QLocalSocket(parent)
{
    connect(this, &Client::readyRead, this, &Client::readyToRead);
    connect(this, QOverload<QLocalSocket::LocalSocketError>::of(&Client::error), this, [this](QLocalSocket::LocalSocketError socketError){
        qDebug()<<"Error code:"<<socketError;
        qDebug()<<errorString();
    });
}

Client::~Client()
{

}

void Client::sendMessage(const QString &msg)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << msg;

    write(data);
    flush();
}

void Client::readyToRead()
{
    QDataStream stream(readAll());
    stream.setVersion(QDataStream::Qt_5_12);
    // readyRead won't be triggered every time, sometimes we will receive several packets at the same time even using flush()
    // You can call bytesAvailable() to check so here we must use while 
    while (!stream.atEnd())
    {
        stream.startTransaction();
        QImage image;
        stream >> image;
        // make sure what we receive is completed
        if (!stream.commitTransaction())
            return;
        emit receiveImage(image);
    }
}
