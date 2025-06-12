#include "Server.h"
#include <QDataStream>
#include <QDebug>
#include <QLocalSocket>

Server::Server(QObject *parent) : QLocalServer(parent) { init(); }

Server::~Server() {}

bool Server::start() { return this->listen("KangarooLove"); }

void Server::sendMessage(const QString &msg) {
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << msg;

    for (auto &socket : m_clientSockets) {
        socket->write(data);
        socket->flush();
    }
}

void Server::readyRead() {
    QLocalSocket *socket = static_cast<QLocalSocket *>(this->sender());
    if (!socket) return;

    auto it = std::find(m_clientSockets.begin(), m_clientSockets.end(), socket);
    if (it == m_clientSockets.end()) return;

    QDataStream stream(socket->readAll());
    stream.setVersion(QDataStream::Qt_5_12);
    while (!stream.atEnd()) {
        stream.startTransaction();
        QString msg;
        stream >> msg;
        // make sure what we receive is completed
        if (!stream.commitTransaction()) return;
        emit receiveMessage(msg);
    }
}

void Server::init() {
    connect(this, &Server::newConnection, this, &Server::newDeviceConnected);
}

void Server::newDeviceConnected() {
    QLocalSocket *socket = this->nextPendingConnection();
    connect(socket, &QLocalSocket::readyRead, this, &Server::readyRead);
    m_clientSockets.push_back(socket);
    sendMessage("Hello client!");
}
