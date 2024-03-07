#include "DaqcServer.h"
#include "DaqcServerHandleReceiveMessageTask.h"
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

HandleReceiveMessageTask *DaqcServer::generateHandleRequestTask(const QByteArray& data)
{
    return new DaqcServerHandleReceiveMessageTask(this, data);
}
