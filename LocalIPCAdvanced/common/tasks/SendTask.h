#pragma once

#include <QRunnable>

class Packet;
class Server;

class SendTask : public QRunnable
{
public:
    SendTask(Server* server, Packet* packet);
    ~SendTask();
    void run() override;
protected:
    Server* m_server;
    Packet* m_packet;
};