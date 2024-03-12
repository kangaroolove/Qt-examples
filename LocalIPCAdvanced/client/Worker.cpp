#include "Worker.h"
#include <QLocalSocket>
#include <QDataStream>

Worker::Worker(QObject* parent) :
    QLocalSocket(parent),
    m_in(new QDataStream)
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