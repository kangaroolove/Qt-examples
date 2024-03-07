#pragma once

#include "Server.h"

class DaqcServer : public Server
{
    Q_OBJECT
public:
    DaqcServer(QObject* parent = nullptr);
    ~DaqcServer();
    void start() override;
protected:
    HandleReceiveMessageTask* generateHandleRequestTask(const QByteArray& data) override;
private:

};