#pragma once

#include "Server.h"

class DaqcServer : public Server
{
public:
    DaqcServer();
    ~DaqcServer();
    void start() override;
protected:
    HandleRequestTask* generateHandleRequestTask() override;
private:

};