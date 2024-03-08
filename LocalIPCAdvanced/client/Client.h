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
    Client(QEventLoop* eventLoop, QObject* parent = nullptr);
    ~Client();
    void insertRequestResult(const QString& messageId, const RequestResult& value);
    RequestResult getRequestResult(const QString& messageId);
signals:
    void receiveMessage(const QByteArray& msg);
public slots:
    void sendMessage(const QByteArray& msg) override;
    void connectServer();
private slots:
    void readyToRead();
protected:
    QDataStream* m_in;
    QEventLoop* m_eventLoop;
    // key: messageId
    std::map<QString, RequestResult> m_resultMap;
};