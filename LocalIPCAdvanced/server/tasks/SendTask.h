#pragma once

#include <QRunnable>

class Packet;
class CommunicationDevice;

class SendTask : public QRunnable
{
public:
    SendTask(CommunicationDevice* device, Packet* packet);
    ~SendTask();
    void run() override;
protected:
    CommunicationDevice* m_device;
    Packet* m_packet;
};