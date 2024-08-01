#pragma once

#include <QLocalServer>
#include <vector>
#include <QImage>

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
    void sendImage(const QImage& image);
signals:
    void receiveMessage(const QString& msg);
private slots:
    void newDeviceConnected();
    void readyRead();
private:
    void init();
    std::vector<QLocalSocket*> m_clientSockets;
};