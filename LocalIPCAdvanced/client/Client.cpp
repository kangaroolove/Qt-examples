#include "Client.h"
#include <QDataStream>
#include <QDebug>

Client::Client(QObject* parent)
    : QLocalSocket(parent)
    , in(new QDataStream(this))
{
    in->setVersion(QDataStream::Qt_5_12);
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

void Client::readyToRead()
{
    qDebug()<<"bytesAvailable"<<this->bytesAvailable();
    if (this->bytesAvailable() > 0 && !in->atEnd())
    {
        quint32 headerFirst = 0;
        quint32 headerSecond = 0;
            
        QByteArray msg;
        *in >> msg;
        emit receiveMessage(msg);
    }
}
