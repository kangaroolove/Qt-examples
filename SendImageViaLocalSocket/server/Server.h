#pragma once

#include <QLocalServer>
#include <vector>

class QLocalSocket;
class QDataStream;

class Server : public QLocalServer
{
    Q_OBJECT
public:
    Server(QObject* parent = nullptr);
    ~Server();
    bool start();
    void sendMessage(const QString& msg);
signals:
    void receiveMessage(const QString& msg);
private slots:
    void newDeviceConnected();
    void readyRead();
private:
    void init();
    std::vector<QLocalSocket*> m_clientSockets;
};