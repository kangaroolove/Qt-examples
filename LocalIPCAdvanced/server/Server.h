#pragma once

#include <QLocalServer>
#include <map>

class QLocalSocket;
class QDataStream;
class HandleRequestTask;

class Server : public QLocalServer
{
    Q_OBJECT
public:
    Server(QObject* parent = nullptr);
    ~Server();
    virtual void start() = 0;
    void sendMessage(const QByteArray& msg);
signals:
    void receiveMessage(const QByteArray& msg);
protected:
    virtual HandleRequestTask* generateHandleRequestTask(const QByteArray& data) = 0;
private slots:
    void newDeviceConnected();
    void readyRead();
    void clientDisconnected();
private:
    void init();
    std::map<QLocalSocket*, QDataStream*> m_clientSockets;
};