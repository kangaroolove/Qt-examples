#pragma once

#include <QObject>
#include <map>
#include <QString>
#include <QImage>
#include <QVariant>

class QDataStream;
class QEventLoop;
class Worker;
class QThread;

class RequestResult
{
public:
    RequestResult() {}
    QString valueType;
    QVariant value;
};

class Client : public QObject
{
    Q_OBJECT
public:
    Client(QObject* parent = nullptr);
    ~Client();
    virtual void start() = 0;
    void insertRequestResult(const QString& messageId, const RequestResult& value);
    RequestResult getRequestResult(const QString& messageId);
signals:
    void messageToWorkerSended(const QByteArray& msg);
    void quitEventloop();
    void imageReceived(QImage image);
public slots:
    void sendMessage(const QByteArray& msg);
    //void connectServer();
protected slots:
    bool isImagePacket(const QJsonDocument& document);
    virtual void receiverMessageFromWorker(const QByteArray& msg) = 0;
private slots:
    //void readyToRead();
    //void receiverMessageFromWorker(const QString& msg);

protected:
    Worker* m_worker;
    QThread* m_thread;
    // key: messageId
    std::map<QString, RequestResult> m_resultMap;
};