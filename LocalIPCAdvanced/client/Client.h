#pragma once

#include "Worker.h"
#include <QObject>
#include <map>
#include <QString>
#include <QImage>
#include <QVariant>

class QDataStream;
class QEventLoop;
class Worker;
class QThread;
class Packet;

class Client : public QObject
{
    Q_OBJECT
public:
    Client(QObject* parent = nullptr);
    ~Client();
    virtual void start() = 0;
signals:
    void messageToWorkerSended(const QByteArray& msg);
    void messageReceived(const QByteArray& msg);
public slots:
    void sendMessage(const QByteArray& msg);
protected:
    QVariant createGetRequest(std::function<Packet *()> callback);
    void createUpdateRequest(Packet *packet);

    Worker* m_worker;
    QThread* m_thread;
    // key: messageId
    std::map<QString, RequestResult> m_resultMap;
private slots:
    void requestResultInserted(const QString& clientMessageId, const RequestResult& result);
    RequestResult getRequestResult(const QString& messageId);
};