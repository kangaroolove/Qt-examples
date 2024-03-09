#pragma once

#include <QObject>
#include <functional>
#include <QVariant>

class QThread;
class Client;
class QEventLoop;
class Packet;

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
    QVariant createGetRequest(std::function<Packet*()> callback);
    void createUpdateRequest(Packet* packet);

    QThread* m_thread;
    Client* m_client;
};