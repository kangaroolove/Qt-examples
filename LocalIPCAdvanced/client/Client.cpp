#include "Client.h"
#include "DaqcClientHandleReceiveMessageTask.h"
#include <QDataStream>
#include <QEventLoop>
#include <QDebug>
#include <QUuid>
#include <QThreadPool>

Client::Client(QObject* parent)
    : QLocalSocket(parent)
    , in(new QDataStream(this))
{
    in->setVersion(QDataStream::Qt_5_12);
    connect(this, &Client::readyRead, this, &Client::readyToRead);
}

Client::~Client()
{

}

void Client::sendMessage(const QByteArray &msg, const QString& messageId)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << msg;

    this->write(data);
    this->flush();

    QEventLoop* eventLoop = new QEventLoop(this);
    m_eventLoopMap.insert({messageId, eventLoop});
    eventLoop->exec();
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

void Client::insertResult(const QString& messageId, const QVariant& value)
{
    m_resultMap.insert({messageId, value});
}

QVariant Client::getResult(const QString &messageId)
{
    QVariant value;
    auto it = m_resultMap.find(messageId);
    if (it != m_resultMap.end())
    {
        value = it->second;
        m_resultMap.erase(it);
        return value;
    }

    qCritical()<<"Cannot find the result";
    return value;
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
