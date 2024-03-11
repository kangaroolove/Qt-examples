#include "Worker.h"
#include <QLocalSocket>
#include <QDataStream>

Worker::Worker(QObject* parent) :
    QObject(parent),
    m_localSocket(new QLocalSocket(this)),
    m_in(new QDataStream)
{
    m_in->setVersion(QDataStream::Qt_5_12);
    connect(m_localSocket, &QLocalSocket::readyRead, this, &Worker::readyRead);
}

Worker::~Worker()
{
    delete m_in;
}

void Worker::connectToServer(const QString &name)
{
    m_localSocket->connectToServer(name);
}

void Worker::readyRead()
{
    if (m_localSocket->bytesAvailable() > 0 && !m_in->atEnd())
    {  
        QByteArray msg;
        *m_in >> msg;
        emit messageReceived(msg);
    }
}

void Worker::sendMessage(const QByteArray &msg)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << msg;

    m_localSocket->write(data);
    m_localSocket->flush();
}