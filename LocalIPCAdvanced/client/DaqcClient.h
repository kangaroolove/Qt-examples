#pragma once

#include <QObject>

class QThread;
class Client;
class QEventLoop;

class DaqcClient : public QObject
{
    Q_OBJECT
public:
    DaqcClient(QObject* parent = nullptr);
    ~DaqcClient();
    void start();
    int testGetApi();
    void testSetApi(bool isTest);
signals:
    void sendMessage(const QByteArray& msg);
    void connectServer();
    void receiveMessage(const QByteArray& msg);
private:
    QEventLoop* m_eventLoop;
    QThread* m_thread;
    Client* m_client;
};