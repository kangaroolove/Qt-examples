#pragma once

#include "ClientWorker.h"
#include <QObject>
#include <map>
#include <QString>
#include <QImage>
#include <QVariant>

class QDataStream;
class QEventLoop;
class ClientWorker;
class QThread;
class Packet;
class QMutex;

class RequestResult
{
public:
    RequestResult() {}
    ~RequestResult() {}
    RequestResult(const QVariant& valueTypes, const QVariant& values) {
        this->values = values;
        this->valueTypes = valueTypes;
    }
    QVariant valueTypes;
    QVariant values;
};

class Client : public QObject
{
    Q_OBJECT
public:
    Client(QObject* parent = nullptr);
    ~Client();
    virtual void connectToServer() = 0;
    void insertRequestResult(const QString& clientMessageId, const RequestResult& result);
signals:
    void messageToWorkerSended(const QByteArray& msg);
    void messageReceived(const QByteArray& msg);
    void imageReceived(QImage image);
public slots:
    void sendMessage(const QByteArray& msg);
protected:
    QVariant createGetRequest(std::function<Packet *()> callback);
    void createUpdateRequest(Packet *packet);
    RequestResult getRequestResult(const QString& clientMessageId);

    ClientWorker* m_worker;
    QThread* m_thread;
    QMutex* m_mutex;
    // shared resources
    // key: clientMessageId
    std::map<QString, RequestResult> m_resultMap;
};