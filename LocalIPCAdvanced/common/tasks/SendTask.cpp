#include "SendTask.h"
#include "Server.h"
#include "Packet.h"

SendTask::SendTask(Server* server, Packet* packet) :
    m_server(server),
    m_packet(packet)
{

}

SendTask::~SendTask()
{

}

void SendTask::run()
{
    m_server->sendMessage(m_packet->toJson());
}
