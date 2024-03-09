#include "SendTask.h"
#include "Packet.h"
#include "Server.h"

SendTask::SendTask(Server* server, Packet* packet) :
    m_server(server),
    m_packet(packet)
{

}

SendTask::~SendTask()
{
    if (m_packet)
        m_packet->deleteLater();
}

void SendTask::run()
{
    m_server->sendMessage(m_packet->toJson());
}
