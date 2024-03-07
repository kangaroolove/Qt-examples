#include "DaqcServer.h"
#include "DaqcHandleRequestTask.h"
#include <QDebug>

DaqcServer::DaqcServer(QObject* parent) :
    Server(parent)
{

}

DaqcServer::~DaqcServer()
{
}

void DaqcServer::start()
{
    qDebug()<<listen("Daqc");
    qDebug()<<"Daqc server started";
}

HandleRequestTask *DaqcServer::generateHandleRequestTask(const QByteArray& data)
{
    return new DaqcHandleRequestTask(this, data);
}
