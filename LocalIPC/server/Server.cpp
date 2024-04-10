#include "Server.h"
#include <QLocalSocket>
#include <QDataStream>
#include <QDebug>

Server::Server(QObject* parent)
    : QLocalServer(parent)
{
    init();
}

Server::~Server()
{

}

bool Server::start()
{
    return this->listen("KangarooLove");
}

void Server::sendMessage(const QString &msg)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << msg;

    for (auto it = m_clientSockets.begin(); it != m_clientSockets.end(); it++)
    {
        (*it)->write(data);
        (*it)->flush();
    }
}

void Server::readyRead()
{
    QLocalSocket* socket = static_cast<QLocalSocket*>(this->sender());
    if (!socket)
        return;

    auto it = std::find(m_clientSockets.begin(), m_clientSockets.end(), socket);
    if (it == m_clientSockets.end())
        return;

    if (socket->bytesAvailable() <= 0)
        return;
    
    QDataStream stream(socket->readAll());
    stream.setVersion(QDataStream::Qt_5_12);
    if (!stream.atEnd())
    {
        QString msg;
        stream >> msg;
        emit receiveMessage(msg);
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
    m_clientSockets.push_back(socket);
    sendMessage("Hello client!");
}
