#pragma once

#include <QObject>
#include <QRunnable>
#include "ReplyPacket.h"

class Server;
class GetValueTask : public QRunnable
{
public:
    GetValueTask(Server* server, const QString& parameter, const QString& clientMessageId);
    ~GetValueTask();
    void run() override;
signals:
    void sendMessage(const QByteArray& msg);
private:
    QString m_parameter;
    QString m_clientMessageId;
    Server* m_server;
};