#include "ClientWorker2.h"
#include <QThread>
#include <QLocalSocket>
#include <QDataStream>
#include <QDebug>
#include <QEventLoop>

ClientWorker2::ClientWorker2(QObject* parent)
    : QObject(parent)
{
    
}

void ClientWorker2::sendMessage(const QString& msg)
{
    qDebug()<<"Send";
    qDebug()<<"ClientWorker2 = "<<QThread::currentThreadId();

    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << msg;

    m_socket->write(data);
}

void ClientWorker2::readyRead()
{
    qDebug()<<"Receive";
    qDebug()<<"ClientWorker2 = "<<QThread::currentThreadId();
    QByteArray data;
    QDataStream stream(m_socket->readAll());
    stream.setVersion(QDataStream::Qt_5_12);
    stream >> data;
    qDebug()<<data;
    emit receiveMessage(data);
}

void ClientWorker2::connectToServer(const QString& name)
{
    m_socket = new QLocalSocket(this);
    m_socket->connectToServer(name);

    QEventLoop loop;
    connect(m_socket, &QLocalSocket::readyRead, this, &ClientWorker2::readyRead);

    loop.exec();

    qDebug()<<"quit loop";
}