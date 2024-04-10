#include "Client.h"
#include <QDataStream>
#include <QDebug>

Client::Client(QObject* parent)
    : QLocalSocket(parent)
{
    connect(this, &Client::readyRead, this, &Client::readyToRead);
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

    this->write(data);
    this->flush();
}

void Client::readyToRead()
{
    if (bytesAvailable() <= 0)
        return;

    QDataStream stream(readAll());
    stream.setVersion(QDataStream::Qt_5_12);
    if (stream.atEnd())
    {
        QString msg;
        stream >> msg;
        emit receiveMessage(msg);
    }
}
