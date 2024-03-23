#pragma once

#include "ReplyPacket.h"
#include "daqclib.h"
#include <QObject>
#include <QRunnable>
#include <QReadWriteLock>

using Daqc = DAQCLib::DAQC;

class Server;

class GetValueInfo
{
public:
    QString parameter;
    QVariant valueTypes;
    QVariant values;
    QString clientMessageId;
};
class GetValueTask : public QRunnable
{
public:
    GetValueTask(Server* server, Daqc* daqc, const GetValueInfo& getValueInfo);
    ~GetValueTask();
    void run() override;
signals:
    void sendMessage(const QByteArray& msg);
private:
    ReplyPacketInfo getReplyPacketInfo();

    GetValueInfo m_getValueInfo;
    Server* m_server;
    Daqc* m_daqc;
    static QReadWriteLock m_readWriteLock;
};