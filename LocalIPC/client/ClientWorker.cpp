#include "ClientWorker.h"
#include <QLocalSocket>
#include <QDataStream>
#include <QDebug>

const int ClientWorker::FPS = 1000 / 60;

ClientWorker::ClientWorker(QObject* parent)
    : QThread(parent)
    , m_quit(false)
    //, m_socket(new QLocalSocket(this))
{
}

void ClientWorker::setQuit()
{
    m_quit = true;
}

void ClientWorker::setServerName(const QString& name)
{
    m_serverName = name;
}

void ClientWorker::sendMessage(const QString& msg)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << msg;

    m_socket->write(data);
}

void ClientWorker::run()
{
    m_socket = new QLocalSocket(this);
    m_socket->connectToServer(m_serverName);

    while (!m_quit)
    {
        if (m_socket->waitForReadyRead(FPS))
        {
            QByteArray data;
            QDataStream stream(m_socket->readAll());
            stream.setVersion(QDataStream::Qt_5_12);
            stream >> data;
            qDebug()<<data;
            emit receiveMessage(data);
        }
    }
}
