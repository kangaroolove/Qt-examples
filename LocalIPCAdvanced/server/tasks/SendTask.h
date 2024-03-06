#pragma once

#include <QRunnable>
#include <QByteArray>

class Server;

class SendTask : public QRunnable
{
public:
    SendTask(Server* server, const QByteArray& data);
    ~SendTask();
    void run() override;
protected:
    Server* m_server;
    QByteArray m_data;
};