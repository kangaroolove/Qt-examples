#pragma once

#include <QLocalSocket>

class QDataStream;
class Client;
class QSharedMemory;

class ClientWorker : public QLocalSocket
{
    Q_OBJECT
public:
    ClientWorker(Client* client, QObject* parent = nullptr);
    ~ClientWorker();
signals:
    void imageReceived(QImage image);
public slots:
    void sendMessage(const QByteArray &msg);
private slots:
    void readyToRead();
private:
    QString getPacketType(const QJsonDocument &document);
    void loadFromMemory();

    Client* m_client;
    QSharedMemory* m_sharedMemory;
};