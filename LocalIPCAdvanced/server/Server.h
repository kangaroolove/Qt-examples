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
    virtual ~Server();
    virtual void start() = 0;
signals:
    void receiveMessage(const QByteArray& msg);
public slots:
    void sendMessage(const QByteArray& msg);
protected:
    virtual HandleReceiveMessageTask* generateHandleRequestTask(const QByteArray& data) = 0;
    virtual void handleReceive(const QByteArray& data) = 0;
private slots:
    void newDeviceConnected();
    void readyRead();
    void clientDisconnected();
private:
    void init();
    std::vector<QLocalSocket*> m_clientSockets;
};