#pragma once

#include "ReplyPacket.h"
#include <QObject>
#include <QRunnable>
#include <QReadWriteLock>

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
    ReplyPacketInfo getReplyPacketInfo();

    QString m_parameter;
    QString m_clientMessageId;
    Server* m_server;
    static QReadWriteLock m_readWriteLock;
};