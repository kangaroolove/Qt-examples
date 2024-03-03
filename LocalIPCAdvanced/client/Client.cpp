#include "Client.h"
#include <QDataStream>
#include <QDebug>

const quint32 Client::HEADER_DATA_FIRST = 0xAA;
const quint32 Client::HEADER_DATA_SECOND = 0xCC;

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

void Client::sendMessage(const QString &msg)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << HEADER_DATA_FIRST;
    out << HEADER_DATA_SECOND;
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
        *in >> headerFirst;
        *in >> headerSecond;
        if ((headerFirst != HEADER_DATA_FIRST) || headerSecond != HEADER_DATA_SECOND)
            return;
            
        QString msg;
        *in >> msg;
        emit receiveMessage(msg);
    }
}
