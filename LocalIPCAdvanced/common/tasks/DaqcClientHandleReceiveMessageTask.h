#pragma once

#include "HandleReceiveMessageTask.h"

class Client;

class DaqcClientHandleReceiveMessageTask : public HandleReceiveMessageTask
{
public:
    DaqcClientHandleReceiveMessageTask(Client* client, const QByteArray& data);
    ~DaqcClientHandleReceiveMessageTask();
protected:
    void analyzeJson(const QByteArray& data) override;
private:
    void handleTask();

    Client* m_client;
};