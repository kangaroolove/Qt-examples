#include "Server.h"
#include "HandleRequestTask.h"
#include <QLocalSocket>
#include <QDataStream>
#include <QDebug>
#include <QThreadPool>

const quint32 Server::HEADER_DATA_FIRST = 0xAA;
const quint32 Server::HEADER_DATA_SECOND = 0xCC;

Server::Server(QObject* parent)
    : QLocalServer(parent)
{
    init();
}

Server::~Server()
{

}

void Server::sendMessage(const QString &msg)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    out << HEADER_DATA_FIRST;
    out << HEADER_DATA_SECOND;
    out << msg;

    for (auto it = m_clientSockets.begin(); it != m_clientSockets.end(); it++)
    {
        it->first->write(data);
        it->first->flush();
    }
}

void Server::readyRead()
{
    QLocalSocket* socket = static_cast<QLocalSocket*>(this->sender());
    if (!socket)
        return;

    auto it = m_clientSockets.find(socket);
    if (it == m_clientSockets.end())
        return;

    qDebug()<<"bytesAvailable"<<socket->bytesAvailable();
    if (socket->bytesAvailable() > 0 && !it->second->atEnd())
    {
        quint32 headerFirst;
        quint32 headerSecond;
        *(it->second) >> headerFirst;
        *(it->second) >> headerSecond;

        if ((headerFirst != HEADER_DATA_FIRST) || headerSecond != HEADER_DATA_SECOND)
            return;

        QByteArray msg;
        *(it->second) >> msg;

        auto task = generateHandleRequestTask(msg);
        QThreadPool::globalInstance()->start(task);

        //emit receiveMessage(msg);
    }
}

void Server::init()
{
    connect(this, &Server::newConnection, this, &Server::newDeviceConnected);
}

void Server::newDeviceConnected()
{
    QLocalSocket* socket = this->nextPendingConnection();
    connect(socket, &QLocalSocket::readyRead, this, &Server::readyRead);
    QDataStream* dataStream = new QDataStream(socket);
    dataStream->setVersion(QDataStream::Qt_5_12);
    m_clientSockets.insert({socket, dataStream});

    sendMessage("Hello client!");
}
