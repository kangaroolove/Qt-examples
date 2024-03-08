#include "Client.h"
#include "DaqcClientHandleReceiveMessageTask.h"
#include <QDataStream>
#include <QEventLoop>
#include <QDebug>
#include <QUuid>
#include <QThreadPool>
#include <QMutexLocker>
#include <QMutex>

Client::Client(QObject* parent) : 
    QLocalSocket(parent), 
    in(new QDataStream(this)),
    m_mutex(new QMutex)
{
    in->setVersion(QDataStream::Qt_5_12);
    connect(this, &Client::readyRead, this, &Client::readyToRead);
}

Client::~Client()
{
    delete m_mutex;
}

void Client::sendMessage(const QByteArray &msg)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << msg;

    this->write(data);
    this->flush();
}

void Client::quitEventLoop(const QString &messageId)
{
    auto it = m_eventLoopMap.find(messageId);
    if (it != m_eventLoopMap.end())
    {
        it->second->quit();
        it->second->deleteLater();
        m_eventLoopMap.erase(it);
    }
}

void Client::insertRequestResult(const QString& messageId, const RequestResult& result)
{
    QMutexLocker locker(m_mutex);
    m_resultMap.insert({messageId, result});
}

RequestResult Client::getRequestResult(const QString &messageId)
{
    QMutexLocker locker(m_mutex);
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

void Client::readyToRead()
{
    if (this->bytesAvailable() > 0 && !in->atEnd())
    {  
        QByteArray msg;
        *in >> msg;
        emit receiveMessage(msg);

        QThreadPool::globalInstance()->start(new DaqcClientHandleReceiveMessageTask(this, msg));
    }
}
