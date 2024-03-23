#include "GetValueTask.h"
#include "SendTask.h"
#include "Server.h"
#include <QThreadPool>

QReadWriteLock GetValueTask::m_readWriteLock;

GetValueTask::GetValueTask(Server* server, Daqc* daqc, const QString& parameter, const QString& clientMessageId) :
    m_parameter(parameter),
    m_clientMessageId(clientMessageId),
    m_server(server),
    m_daqc(daqc)
{

}

GetValueTask::~GetValueTask()
{

}

void GetValueTask::run()
{
    ReplyPacket* packet = new ReplyPacket(getReplyPacketInfo());
    auto task = new SendTask(m_server, packet);
    QThreadPool::globalInstance()->start(task);
}

ReplyPacketInfo GetValueTask::getReplyPacketInfo()
{
    QReadLocker locker(&m_readWriteLock);
    ReplyPacketInfo replyPacketInfo;
    replyPacketInfo.parameter = m_parameter;
    replyPacketInfo.clientMessageId = m_clientMessageId;
    replyPacketInfo.requestType = "get";

    if (replyPacketInfo.parameter == "test")
    {
        replyPacketInfo.value = QVariant(10);
        replyPacketInfo.valueType = "int";
    }
    else if (replyPacketInfo.parameter == PROBE_INFO)
    {
        replyPacketInfo.value = m_daqc->GetProbeInfo();
    }

    return replyPacketInfo;
}
