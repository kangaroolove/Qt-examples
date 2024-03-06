#include "DaqcServer.h"
#include "DaqcHandleRequestTask.h"
#include <QDebug>

DaqcServer::DaqcServer()
{

}

DaqcServer::~DaqcServer()
{

}

void DaqcServer::start()
{
    listen("ABC");
    qDebug()<<"Daqc server started";
}

HandleRequestTask *DaqcServer::generateHandleRequestTask(const QByteArray& data)
{
    return new DaqcHandleRequestTask(data);
}
