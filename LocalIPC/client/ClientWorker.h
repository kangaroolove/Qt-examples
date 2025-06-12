#pragma once

#include <QObject>

class QThread;
class QLocalSocket;

class ClientWorker : public QObject {
    Q_OBJECT
public:
    ClientWorker(QObject *parent = nullptr);
signals:
    void receiveMessage(const QString &msg);
public slots:
    void connectToServer(const QString &name);
    void sendMessage(const QString &msg);
private slots:
    void readyRead();

private:
    QLocalSocket *m_socket;
};