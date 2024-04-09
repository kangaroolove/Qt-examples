#include "Server.h"
#include "HandleReceiveMessageTask.h"
#include <QCoreApplication>
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
    for (auto it = m_clientSockets.begin(); it != m_clientSockets.end(); it++)
    {
        // qInfo()<<"Server send message";
        // qInfo()<<msg;

        it->first->write(msg);
        //it->first->flush();
    }
}

void Server::readyRead()
{
    QMutexLocker locker(m_mutex);
    QLocalSocket* socket = static_cast<QLocalSocket*>(this->sender());
    if (!socket)
        return;

    auto it = m_clientSockets.find(socket);
    if (it == m_clientSockets.end())
        return;

    // In a RTC application, handling message is slower than receiving message sometimes.
    // So we need to use while rather than if here
    while (socket->bytesAvailable() > 0 && !it->second->atEnd())
    {
        QByteArray msg;
        *(it->second) >> msg;
        //qInfo()<<"Server receive message";
		//qInfo()<<msg;
        QThreadPool::globalInstance()->start(generateHandleRequestTask(msg));
    }
}

void Server::clientDisconnected()
{
    QMutexLocker locker(m_mutex);
    QLocalSocket* socket = static_cast<QLocalSocket*>(this->sender());
    if (!socket)
        return;

    auto it = m_clientSockets.find(socket);
    if (it != m_clientSockets.end())
    {
        m_clientSockets.erase(it);
        qInfo()<<"A client is disconnected";
    }

    if (m_clientSockets.empty())
    {
        qInfo()<<"Since client list is empty, server will be closed";
        QCoreApplication::quit();
    }
}

void Server::init()
{
    connect(this, &Server::newConnection, this, &Server::newDeviceConnected);
}

void Server::newDeviceConnected()
{
    qInfo()<<"A client is connected";
    QMutexLocker locker(m_mutex);
    QLocalSocket* socket = this->nextPendingConnection();
    connect(socket, &QLocalSocket::readyRead, this, &Server::readyRead);
    connect(socket, &QLocalSocket::disconnected, this, &Server::clientDisconnected);
    QDataStream* dataStream = new QDataStream(socket);
    dataStream->setVersion(QDataStream::Qt_5_12);
    m_clientSockets.insert({socket, dataStream});
}
