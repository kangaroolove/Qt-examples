#pragma once

#include "CommunicationDevice.h"
#include <QLocalServer>
#include <map>

class QMutex;
class QLocalSocket;
class QDataStream;
class HandleReceiveMessageTask;

class Server : public QLocalServer, public CommunicationDevice
{
    Q_OBJECT
public:
    Server(QObject* parent = nullptr);
    ~Server();
    virtual void start() = 0;
    void sendMessage(const QByteArray& msg) override;
signals:
    void receiveMessage(const QByteArray& msg);
protected:
    virtual HandleReceiveMessageTask* generateHandleRequestTask(const QByteArray& data) = 0;
private slots:
    void newDeviceConnected();
    void readyRead();
    void clientDisconnected();
private:
    void init();
    // shared resources
    std::map<QLocalSocket*, QDataStream*> m_clientSockets;
    QMutex* m_mutex;
};