#pragma once

#include <QObject>

class QThread;
class QLocalSocket;

class ClientWorker2 : public QObject
{
    Q_OBJECT
public:
    ClientWorker2(QObject* parent = nullptr);
signals:
    void receiveMessage(const QString& msg);
public slots:
    void connectToServer(const QString& name);
    void sendMessage(const QString& msg);
private slots:
    void readyRead();
private:
    QLocalSocket* m_socket;
};