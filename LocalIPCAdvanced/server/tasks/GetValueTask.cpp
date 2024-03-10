#include "GetValueTask.h"
#include <ReplyPacket.h>

GetValueTask::GetValueTask(Server* server, const QString& parameter, const QString& clientMessageId) :
    m_parameter(parameter),
    m_clientMessageId(clientMessageId),
    m_server(server)
{

}

GetValueTask::~GetValueTask()
{

}

void GetValueTask::run()
{
    if (m_parameter == "test")
    {
    }

    //ReplyPacket* packet = new ReplyPacket();
}
