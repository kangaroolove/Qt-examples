#pragma once

#include <QLocalSocket>

class QDataStream;
class Client;

class Worker : public QLocalSocket
{
    Q_OBJECT
public:
    Worker(Client* client, QObject* parent = nullptr);
    ~Worker();
signals:
    void imageReceived(const QImage& image);
    void eventLoopQuitted();
    void messageReceived(const QByteArray& msg);
public slots:
    void sendMessage(const QByteArray &msg);
private slots:
    void readyToRead();
private:
    bool isImagePacket(const QJsonDocument &document);

    QDataStream* m_in;
    Client* m_client;
};