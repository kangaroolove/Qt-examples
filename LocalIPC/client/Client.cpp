#include "Client.h"
#include "ClientWorker2.h"
#include <QThread>
#include <QDataStream>
#include <QDebug>

Client::Client(QObject* parent)
    : QObject(parent)
    , m_clientWorker2(new ClientWorker2())
    , m_thread(new QThread(this))
{
    qDebug()<<"main thread = "<<QThread::currentThreadId();

    connect(this, &Client::connectToServerFromWorker, m_clientWorker2, &ClientWorker2::connectToServer);
    connect(this, &Client::sendMessageToWorker, m_clientWorker2, &ClientWorker2::sendMessage);
    m_clientWorker2->moveToThread(m_thread);
    m_thread->start();
}

Client::~Client()
{
    emit quitThread();
    m_thread->quit();
    m_thread->wait();
}

void Client::sendMessage(const QString &msg)
{
    emit sendMessageToWorker(msg);
}

void Client::connectToServer(const QString& name)
{
    emit connectToServerFromWorker(name);
}
