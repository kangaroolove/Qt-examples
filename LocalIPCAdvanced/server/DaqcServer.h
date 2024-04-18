#pragma once

#include "Server.h"


class QTimer;
class ServerWorker;
class QThread;
class DaqcServer : public Server
{
    Q_OBJECT
public:
    DaqcServer(QObject* parent = nullptr);
    ~DaqcServer();
    void start() override;
signals:
    void handleUpdateRequest(const QString &parameter, const QVariant &valueTypes, const QVariant &values);
protected:
    HandleReceiveMessageTask* generateHandleRequestTask(const QByteArray& data) override;
    void handleReceive(const QByteArray& data) override;
private:
    QString getPacketType(const QJsonDocument &document) const;
    QString getRequestType(const QJsonDocument &document) const;

    ServerWorker* m_worker;
    QThread* m_thread;
};