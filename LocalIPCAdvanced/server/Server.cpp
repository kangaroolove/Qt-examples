#include "Server.h"
#include "HandleRequestTask.h"
#include <QLocalSocket>
#include <QDataStream>
#include <QDebug>
#include <QThreadPool>
#include <QMutex>

Server::Server(QObject* parent) : 
    QLocalServer(parent), 
    m_mutex(new QMutex)
{
    init();
}

Server::~Server()
{
    delete m_mutex;
}

void Server::sendMessage(const QByteArray &msg)
{
    QMutexLocker locker(m_mutex);
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

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

    if (socket->bytesAvailable() > 0 && !it->second->atEnd())
    {
        QByteArray msg;
        *(it->second) >> msg;
        qDebug()<<msg;

        auto task = generateHandleRequestTask(msg);
        QThreadPool::globalInstance()->start(task);

        //emit receiveMessage(msg);
    }
}

void Server::clientDisconnected()
{
    QMutexLocker locker(m_mutex);
    qDebug()<<"Server::clientDisconnected";
    QLocalSocket* socket = static_cast<QLocalSocket*>(this->sender());
    if (!socket)
        return;

    auto it = m_clientSockets.find(socket);
    if (it != m_clientSockets.end())
        m_clientSockets.erase(it);
}

void Server::init()
{
    connect(this, &Server::newConnection, this, &Server::newDeviceConnected);
}

void Server::newDeviceConnected()
{
    QLocalSocket* socket = this->nextPendingConnection();
    connect(socket, &QLocalSocket::readyRead, this, &Server::readyRead);
    connect(socket, &QLocalSocket::disconnected, this, &Server::clientDisconnected);
    QDataStream* dataStream = new QDataStream(socket);
    dataStream->setVersion(QDataStream::Qt_5_12);
    m_clientSockets.insert({socket, dataStream});
    sendMessage("Hello client!");
}
