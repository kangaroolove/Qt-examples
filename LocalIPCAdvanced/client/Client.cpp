#include "Client.h"
#include "Worker.h"
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
    m_worker(new Worker),
    m_thread(new QThread(this))
{
    m_worker->moveToThread(m_thread);
    connect(m_thread, &QThread::finished, m_worker, &Worker::deleteLater);
    connect(m_worker, &Worker::requestResultInserted, this, &Client::requestResultInserted);
    connect(this, &Client::messageToWorkerSended, m_worker, &Worker::sendMessage);
    connect(m_worker, &Worker::messageReceived, this, &Client::messageReceived);
    m_thread->start();
}

Client::~Client()
{
    m_thread->quit();
    m_thread->wait();
}

RequestResult Client::getRequestResult(const QString &messageId)
{
    RequestResult result;
    auto it = m_resultMap.find(messageId);
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

void Client::requestResultInserted(const QString& clientMessageId, const RequestResult& result)
{
    m_resultMap.insert({clientMessageId, result});
}

QVariant Client::createGetRequest(std::function<Packet*()> callback)
{
    QEventLoop eventloop;
    connect(this, &Client::requestResultInserted, &eventloop, &QEventLoop::quit);

    Packet* packet = callback();
    sendMessage(packet->toJson());
    eventloop.exec();

    RequestResult result = getRequestResult(packet->getMessageId());
    packet->deleteLater();
    return result.value;
}
