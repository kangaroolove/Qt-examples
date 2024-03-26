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
    else if (replyPacketInfo.parameter == DaqcParameter::SCAN_MODE)
    {
        replyPacketInfo.value = m_daqc->scanMode();
        replyPacketInfo.valueType = "int";
    }
    else if (replyPacketInfo.parameter == DaqcParameter::GET_PARAMETER)
    {
        replyPacketInfo.value = m_daqc->GetParameter(values.first().toInt());
        replyPacketInfo.valueType = "double";
    }
    else if (replyPacketInfo.parameter == DaqcParameter::B_DYNAMIC)
    {
        replyPacketInfo.value = m_daqc->BDynamic();
        replyPacketInfo.valueType = "int";
    }
    else if (replyPacketInfo.parameter == DaqcParameter::D_DYNAMIC)
    {
        replyPacketInfo.value = m_daqc->DDynamic();
        replyPacketInfo.valueType = "int";
    }
    else if (replyPacketInfo.parameter == DaqcParameter::PERSISTENCE_COLOR)
    {
        replyPacketInfo.value = m_daqc->PersistenceColor();
        replyPacketInfo.valueType = "int";
    }
    else if (replyPacketInfo.parameter == DaqcParameter::PROBE_SEL)
    {
        replyPacketInfo.value = m_daqc->ProbeSEL();
        replyPacketInfo.valueType = "int";
    }
    else if (replyPacketInfo.parameter == DaqcParameter::REGION_PHYSICAL_DELTA_X)
    {
        double x = 0;
        double y = 0;
        m_daqc->GetRegionPhysicalDelta(x, y);
        replyPacketInfo.value = x;
        replyPacketInfo.valueType = "double";
    }
    else if (replyPacketInfo.parameter == DaqcParameter::REGION_PHYSICAL_DELTA_Y)
    {
        double x = 0;
        double y = 0;
        m_daqc->GetRegionPhysicalDelta(x, y);
        replyPacketInfo.value = y;
        replyPacketInfo.valueType = "double";
    }
    else if (replyPacketInfo.parameter == DaqcParameter::B_GAIN)
    {
        replyPacketInfo.value = m_daqc->BGain();
        replyPacketInfo.valueType = "int";
    }
    else if (replyPacketInfo.parameter == DaqcParameter::C_GAIN)
    {
        replyPacketInfo.value = m_daqc->CGain();
        replyPacketInfo.valueType = "int";
    }
    else if (replyPacketInfo.parameter == DaqcParameter::XML_DEPTH)
    {
        replyPacketInfo.value = m_daqc->GetParameter(50);
        replyPacketInfo.valueType = "double";
    }
    else if (replyPacketInfo.parameter == DaqcParameter::B_FREQUENCY)
    {
        replyPacketInfo.value = m_daqc->Frequence();
        replyPacketInfo.valueType = "double";
    }
    else if (replyPacketInfo.parameter == DaqcParameter::B_FREQUENCY_2)
    {
        replyPacketInfo.value = m_daqc->Freq2();
        replyPacketInfo.valueType = "double";
    }
    else if (replyPacketInfo.parameter == DaqcParameter::FAVG)
    {
        replyPacketInfo.value = m_daqc->FrameRelation();
        replyPacketInfo.valueType = "double";
    }
    else if (replyPacketInfo.parameter == DaqcParameter::LAVG)
    {
        replyPacketInfo.value = m_daqc->LavgRelation();
        replyPacketInfo.valueType = "int";
    }

    return replyPacketInfo;
}
