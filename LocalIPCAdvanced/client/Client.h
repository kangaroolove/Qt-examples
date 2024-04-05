#pragma once

#include "ClientWorker.h"
#include <QObject>
#include <map>
#include <QString>
#include <QImage>
#include <QVariant>
#include <QReadWriteLock>

class QDataStream;
class QEventLoop;
class ClientWorker;
class QThread;
class Packet;
class QReadWriteLock;

class Client : public QObject
{
    Q_OBJECT
public:
    Client(QObject* parent = nullptr);
    ~Client();
    virtual void connectToServer() = 0;
    void updateResult(const QString& parameter, const QVariant& result);
    bool isConnected() const;
signals:
    void messageToWorkerSended(const QByteArray& msg);
    void messageReceived(const QByteArray& msg);
    void imageReceived(QImage image);
    void connected();
    void disconnected();
public slots:
    void sendMessage(const QByteArray& msg);
private slots:
    void onConnected();
    void onDisconnected();
protected:
    void createRequest(Packet *packet);
    QVariant getResult(const QString& parameter) const;

    ClientWorker* m_worker;
    QThread* m_thread;
    QReadWriteLock* m_locker;
    bool m_connected;
    // shared resources
    // key: parameter name
    std::map<QString, QVariant> m_parametersMap;
};