#include "ClientWorker.h"
#include <QDataStream>
#include <QDebug>
#include <QEventLoop>
#include <QLocalSocket>
#include <QThread>

ClientWorker::ClientWorker(QObject *parent)
    : QObject(parent), m_socket(nullptr) {}

void ClientWorker::sendMessage(const QString &msg) {
    if (!m_socket) {
        qDebug() << "Failed to send message. Please connect the server first!";
        return;
    }

    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << msg;

    m_socket->write(data);
}

void ClientWorker::readyRead() {
    QString msg;
    QDataStream stream(m_socket->readAll());
    stream.setVersion(QDataStream::Qt_5_12);
    stream >> msg;

    emit receiveMessage(msg);
}

void ClientWorker::connectToServer(const QString &name) {
    if (!m_socket) {
        m_socket = new QLocalSocket(this);
        connect(m_socket, &QLocalSocket::readyRead, this,
                &ClientWorker::readyRead);
    }
    m_socket->connectToServer(name);
}