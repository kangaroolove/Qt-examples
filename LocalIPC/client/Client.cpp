#include "Client.h"
#include "ClientWorker.h"
#include <QDataStream>
#include <QDebug>
#include <QThread>

Client::Client(QObject *parent)
    : QObject(parent),
      m_clientWorker(new ClientWorker()),
      m_thread(new QThread(this)) {
    connect(this, &Client::connectServer, m_clientWorker,
            &ClientWorker::connectToServer);
    connect(this, &Client::sendMessageToWorker, m_clientWorker,
            &ClientWorker::sendMessage);
    connect(m_thread, &QThread::finished, m_clientWorker,
            &ClientWorker::deleteLater);
    connect(m_clientWorker, &ClientWorker::receiveMessage, this,
            &Client::receiveMessage);

    m_clientWorker->moveToThread(m_thread);
    m_thread->start();
}

Client::~Client() {
    m_thread->quit();
    m_thread->wait();
}

void Client::sendMessage(const QString &msg) { emit sendMessageToWorker(msg); }

void Client::connectToServer(const QString &name) { emit connectServer(name); }
