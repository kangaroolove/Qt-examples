#include "SendTask.h"
#include "Packet.h"
#include "Server.h"

SendTask::SendTask(Server* server, Packet* packet) :
    m_packet(packet),
    m_server(server)
{
    // Since server is created by main thread, so we need to use QueuedConnection
    connect(this, &SendTask::sendMessage, m_server, &Server::sendMessage, Qt::QueuedConnection);
}

SendTask::~SendTask()
{
    if (m_packet)
        m_packet->deleteLater();
}

void SendTask::run()
{
    emit sendMessage(m_packet->toBinary());
}
