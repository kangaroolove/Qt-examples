#include "SendTask.h"
#include "Server.h"

SendTask::SendTask(Server* server, const QByteArray& data) :
    m_server(server),
    m_data(data)
{

}

SendTask::~SendTask()
{

}

void SendTask::run()
{
    m_server->sendMessage(m_data);
}
