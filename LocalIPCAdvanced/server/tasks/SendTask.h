#pragma once

#include <QObject>
#include <QRunnable>

class Packet;
class Server;

class SendTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    SendTask(Packet* packet);
    ~SendTask();
    void run() override;
signals:
    void sendMessage(const QByteArray& msg);
protected:
    Packet* m_packet;
};