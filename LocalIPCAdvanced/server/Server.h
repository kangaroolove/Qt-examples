#pragma once

#include <QLocalServer>
#include <map>

class QMutex;
class QLocalSocket;
class QDataStream;
class HandleReceiveMessageTask;

class Server : public QLocalServer
{
    Q_OBJECT
public:
    Server(QObject* parent = nullptr);
    ~Server();
    virtual void start() = 0;
signals:
    void receiveMessage(const QByteArray& msg);
public slots:
    void sendMessage(const QByteArray& msg);
protected:
    virtual HandleReceiveMessageTask* generateHandleRequestTask(const QByteArray& data) = 0;
private slots:
    void newDeviceConnected();
    void readyRead();
    void clientDisconnected();
private:
    void init();
    QMutex* m_mutex;
    // shared resources
    std::map<QLocalSocket*, QDataStream*> m_clientSockets;
};