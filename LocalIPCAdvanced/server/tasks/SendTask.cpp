#include "SendTask.h"
#include "Packet.h"
#include "Server.h"

SendTask::SendTask(Packet* packet) :
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
    emit sendMessage(m_packet->toJson());
}
