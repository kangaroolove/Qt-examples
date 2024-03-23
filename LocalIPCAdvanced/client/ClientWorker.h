#pragma once

#include <QLocalSocket>

class QDataStream;
class Client;

class ClientWorker : public QLocalSocket
{
    Q_OBJECT
public:
    ClientWorker(Client* client, QObject* parent = nullptr);
    ~ClientWorker();
signals:
    void imageReceived(const QImage& image);
    void eventLoopQuitted();
    void messageReceived(const QByteArray& msg);
public slots:
    void sendMessage(const QByteArray &msg);
private slots:
    void readyToRead();
private:
    QString getPacketType(const QJsonDocument &document);

    QDataStream* m_in;
    Client* m_client;
};