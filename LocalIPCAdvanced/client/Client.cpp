#include "Client.h"
#include <QDataStream>
#include <QEventLoop>
#include <QDebug>
#include <QUuid>

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

void Client::sendMessage(const QByteArray &msg, const QString& messageId)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << msg;

    this->write(data);
    this->flush();

    QEventLoop* eventLoop = new QEventLoop(this);
    m_eventLoopMap.insert({eventLoop, messageId});
    eventLoop->exec();
}

void Client::readyToRead()
{
    if (this->bytesAvailable() > 0 && !in->atEnd())
    {  
        QByteArray msg;
        *in >> msg;
        emit receiveMessage(msg);
    }
}
