#include "ClientWorker.h"
#include <QThread>
#include <QLocalSocket>
#include <QDataStream>
#include <QDebug>
#include <QEventLoop>

ClientWorker::ClientWorker(QObject* parent)
    : QObject(parent)
{
    
}

void ClientWorker::sendMessage(const QString& msg)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << msg;

    m_socket->write(data);
}

void ClientWorker::readyRead()
{
    QByteArray data;
    QDataStream stream(m_socket->readAll());
    stream.setVersion(QDataStream::Qt_5_12);
    stream >> data;
    
    emit receiveMessage(data);
}

void ClientWorker::connectToServer(const QString& name)
{
    m_socket = new QLocalSocket(this);
    m_socket->connectToServer(name);

    QEventLoop loop;
    connect(m_socket, &QLocalSocket::readyRead, this, &ClientWorker::readyRead);
    loop.exec();
}