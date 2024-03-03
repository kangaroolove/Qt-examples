#include "DaqcServer.h"
#include "DaqcHandleRequestTask.h"

DaqcServer::DaqcServer()
{

}

DaqcServer::~DaqcServer()
{

}

void DaqcServer::start()
{
    listen("Daqc");
}

HandleRequestTask *DaqcServer::generateHandleRequestTask()
{
    return new DaqcHandleRequestTask;
}
