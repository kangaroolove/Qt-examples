#pragma once

#include <QByteArray>

class CommunicationDevice
{
public:
    CommunicationDevice();
    ~CommunicationDevice();
    virtual void sendMessage(const QByteArray &msg) = 0;
};