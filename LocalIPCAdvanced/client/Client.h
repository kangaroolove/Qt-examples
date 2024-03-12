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

class Client : public QObject
{
    Q_OBJECT
public:
    Client(QObject* parent = nullptr);
    ~Client();
    virtual void start() = 0;
signals:
    void messageToWorkerSended(const QByteArray& msg);
public slots:
    void sendMessage(const QByteArray& msg);
protected slots:
    virtual void receiverMessageFromWorker(const QByteArray& msg) = 0;
private slots:
    void requestResultInserted(const QString& clientMessageId, const RequestResult& result);
    RequestResult getRequestResult(const QString& messageId);
protected:
    Worker* m_worker;
    QThread* m_thread;
    // key: messageId
    std::map<QString, RequestResult> m_resultMap;
};