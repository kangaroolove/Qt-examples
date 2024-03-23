#include "GetValueTask.h"
#include "SendTask.h"
#include "Server.h"
#include "StringDef.h"
#include <QThreadPool>

QReadWriteLock GetValueTask::m_readWriteLock;

GetValueTask::GetValueTask(Server* server, Daqc* daqc, const GetValueInfo& getValueInfo) :
    m_getValueInfo(getValueInfo),
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
    replyPacketInfo.parameter = m_getValueInfo.parameter;
    replyPacketInfo.clientMessageId = m_getValueInfo.clientMessageId;
    replyPacketInfo.requestType = "get";

    auto values = m_getValueInfo.values.toList();
    auto valueTypes = m_getValueInfo.valueTypes.toStringList();

    if (replyPacketInfo.parameter == "test")
    {   
        replyPacketInfo.value = 10;
        replyPacketInfo.valueType = "int";
    }
    else if (replyPacketInfo.parameter == DaqcParameter::PROBE_INFO)
    {
        replyPacketInfo.value = m_daqc->GetProbeInfo(values.first().toInt());
        replyPacketInfo.valueType = "int";
    }
    else if (replyPacketInfo.parameter == DaqcParameter::THI)
    {
        replyPacketInfo.value = m_daqc->THI();
        replyPacketInfo.valueType = "int";
    }
    else if (replyPacketInfo.parameter == DaqcParameter::C_BASE_LINE)
    {
        replyPacketInfo.value = m_daqc->CBaseLine();
        replyPacketInfo.valueType = "int";
    }

    return replyPacketInfo;
}
