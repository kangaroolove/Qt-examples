#pragma once

#include <QLocalSocket>

class QDataStream;

class Client : public QLocalSocket
{
    Q_OBJECT
public:
    Client(QObject* parent = nullptr);
    ~Client();
    void sendMessage(const QString& msg);
signals:
    void receiveMessage(const QString& msg);
private slots:
    void readyToRead();
};