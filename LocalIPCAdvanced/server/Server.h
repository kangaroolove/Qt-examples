#pragma once

#include <QLocalServer>
#include <map>

class QLocalSocket;
class QDataStream;

class Server : public QLocalServer
{
    Q_OBJECT
public:
    Server(QObject* parent = nullptr);
    ~Server();
    virtual void start() = 0;
    void sendMessage(const QString& msg);
signals:
    void receiveMessage(const QString& msg);
private slots:
    void newDeviceConnected();
    void readyRead();
private:
    void init();
    std::map<QLocalSocket*, QDataStream*> m_clientSockets;
    static const quint32 HEADER_DATA_FIRST;
    static const quint32 HEADER_DATA_SECOND;
};