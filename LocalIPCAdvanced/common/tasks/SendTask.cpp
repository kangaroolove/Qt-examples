#include "SendTask.h"
#include "Packet.h"
#include "CommunicationDevice.h"

SendTask::SendTask(CommunicationDevice* device, Packet* packet) :
    m_device(device),
    m_packet(packet)
{

}

SendTask::~SendTask()
{
    if (m_packet)
        delete m_packet;
}

void SendTask::run()
{
    m_device->sendMessage(m_packet->toJson());
}
