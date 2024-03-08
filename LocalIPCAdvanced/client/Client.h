#pragma once

#include "CommunicationDevice.h"
#include <QLocalSocket>
#include <map>
#include <QString>

class QDataStream;
class QEventLoop;
class QMutex;

class RequestResult
{
public:
    RequestResult() {}
    QString valueType;
    QVariant value;
};

class Client : public QLocalSocket, public CommunicationDevice
{
    Q_OBJECT
public:
    Client(QObject* parent = nullptr);
    ~Client();
    virtual void start() = 0;
    /**
     * @brief 
     * 
     * @param msg json data
     * @param messageId uuid
     */
    void sendMessage(const QByteArray& msg) override;
    void quitEventLoop(const QString& messageId);
    void insertRequestResult(const QString& messageId, const RequestResult& value);
    RequestResult getRequestResult(const QString& messageId);
signals:
    void receiveMessage(const QByteArray& msg);
private slots:
    void readyToRead();
protected:
    QDataStream* in;
    QMutex* m_mutex;
    // shared variables
    // key: messageId
    std::map<QString, QEventLoop*> m_eventLoopMap;
    // key: messageId
    std::map<QString, RequestResult> m_resultMap;
};