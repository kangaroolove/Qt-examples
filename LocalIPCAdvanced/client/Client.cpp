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
#include <QReadWriteLock>
#include <QEventLoop>
#include <functional>

Client::Client(QObject* parent) : 
    QObject(parent),
    m_worker(new ClientWorker(this)),
    m_thread(new QThread(this)),
    m_locker(new QReadWriteLock),
    m_connected(false)
{
    m_worker->moveToThread(m_thread);
    connect(m_thread, &QThread::finished, m_worker, &ClientWorker::deleteLater);
    connect(this, &Client::messageToWorkerSended, m_worker, &ClientWorker::sendMessage);
    connect(m_worker, &ClientWorker::imageReceived, this, &Client::imageReceived);
    connect(m_worker, &ClientWorker::connected, this, &Client::onConnected);
    connect(m_worker, &ClientWorker::disconnected, this, &Client::onDisconnected);
    m_thread->start();
}

Client::~Client()
{
    m_thread->quit();
    m_thread->wait();

    delete m_locker;
}

void Client::updateResult(const QString &parameter, const QVariant& result)
{
    QWriteLocker locker(m_locker);
    bool exist = m_parametersMap.count(parameter) > 0;
    if (!exist)
    {
        m_parametersMap.insert({parameter, result});
        return;
    }

    if (m_parametersMap.at(parameter) != result)
        m_parametersMap[parameter] = result;
}

bool Client::isConnected() const
{
    return m_connected;
}

void Client::sendMessage(const QByteArray& msg)
{
    emit messageToWorkerSended(msg);
}

void Client::onConnected()
{
    m_connected = true;
    emit connected();
}

void Client::onDisconnected()
{
    m_connected = false;
    emit disconnected();
}

void Client::createRequest(Packet *packet)
{
    sendMessage(packet->toBinary());
    packet->deleteLater();
}

QVariant Client::getResult(const QString &parameter) const
{
    QReadLocker locker(m_locker);
    auto it = m_parametersMap.find(parameter);
    if (it != m_parametersMap.end())
        return it->second;

    qCritical()<<"Client::getResult --- get "<<parameter<<" Cannot find the result";
    return QVariant();
}
