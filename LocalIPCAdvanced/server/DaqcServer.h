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
    HandleRequestTask* generateHandleRequestTask(const QByteArray& data) override;
private:

};