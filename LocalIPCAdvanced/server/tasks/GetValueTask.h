#pragma once

#include "ReplyPacket.h"
#include "daqclib.h"
#include <QObject>
#include <QRunnable>
#include <QReadWriteLock>

using Daqc = DAQCLib::DAQC;

class Server;
class GetValueTask : public QRunnable
{
public:
    GetValueTask(Server* server, Daqc* daqc, const QString& parameter, const QString& clientMessageId);
    ~GetValueTask();
    void run() override;
signals:
    void sendMessage(const QByteArray& msg);
private:
    ReplyPacketInfo getReplyPacketInfo();

    QString m_parameter;
    QString m_clientMessageId;
    Server* m_server;
    Daqc* m_daqc;
    static QReadWriteLock m_readWriteLock;
};