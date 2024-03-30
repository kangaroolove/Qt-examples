#include "Client.h"
#include "ClientWorker.h"
#include "Packet.h"
#include <QDataStream>
#include <QEventLoop>
#include <QDebug>
#include <QUuid>
#include <QThreadPool>
#include <QMutexLocker>
#include <QMutex>
#include <QJsonDocument>
#include <QJsonObject>
#include <QImage>
#include <QEventLoop>
#include <functional>

Client::Client(QObject* parent) : 
    QObject(parent),
    m_worker(new ClientWorker(this)),
    m_thread(new QThread(this)),
    m_mutex(new QMutex)
{
    m_worker->moveToThread(m_thread);
    connect(m_thread, &QThread::finished, m_worker, &ClientWorker::deleteLater);
    connect(this, &Client::messageToWorkerSended, m_worker, &ClientWorker::sendMessage);
    connect(m_worker, &ClientWorker::messageReceived, this, &Client::messageReceived);
    connect(m_worker, &ClientWorker::imageReceived, this, &Client::imageReceived);
    connect(m_worker, &ClientWorker::connected, this, &Client::connected);
    connect(m_worker, &ClientWorker::disconnected, this, &Client::disconnected);
    m_thread->start();
}

Client::~Client()
{
    m_thread->quit();
    m_thread->wait();

    delete m_mutex;
}

void Client::insertRequestResult(const QString &clientMessageId, const RequestResult &result)
{
    QMutexLocker locker(m_mutex);
    m_resultMap.insert({clientMessageId, result});
}

RequestResult Client::getRequestResult(const QString &clientMessageId)
{
    QMutexLocker locker(m_mutex);
    RequestResult result;
    auto it = m_resultMap.find(clientMessageId);
    if (it != m_resultMap.end())
    {
        result = it->second;
        m_resultMap.erase(it);
        return result;
    }

    qCritical()<<"Cannot find the result";
    return result;
}

void Client::sendMessage(const QByteArray& msg)
{
    emit messageToWorkerSended(msg);
}

QVariant Client::createGetRequest(std::function<Packet*()> callback)
{
    QEventLoop eventloop;
    connect(m_worker, &ClientWorker::eventLoopQuitted, &eventloop, &QEventLoop::quit);

    Packet* packet = callback();
    sendMessage(packet->toJson());
    eventloop.exec();

    RequestResult result = getRequestResult(packet->getMessageId());
    packet->deleteLater();
    return result.values;
}

void Client::createUpdateRequest(Packet *packet)
{
    sendMessage(packet->toJson());
    packet->deleteLater();
}
