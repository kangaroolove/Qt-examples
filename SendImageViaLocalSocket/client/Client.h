#pragma once

#include <QLocalSocket>
#include <QImage>

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
    void receiveImage(QImage image);
public slots:
    void connectServer();     
private slots:
    void readyToRead();
};