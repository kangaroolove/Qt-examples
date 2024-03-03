#pragma once

#include <QLocalSocket>

class QDataStream;

class Client : public QLocalSocket
{
    Q_OBJECT
public:
    Client(QObject* parent = nullptr);
    ~Client();
    virtual void start() = 0;
    void sendMessage(const QByteArray& msg);
signals:
    void receiveMessage(const QByteArray& msg);
private slots:
    void readyToRead();
private:
    QDataStream* in;
};