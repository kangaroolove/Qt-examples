#include "DaqcServer.h"
#include "DaqcServerHandleReceiveMessageTask.h"
#include <QDebug>

DaqcServer::DaqcServer(QObject* parent) :
    Server(parent),
    m_daqc(new Daqc())
{

}

DaqcServer::~DaqcServer()
{
    delete m_daqc;
}

void DaqcServer::start()
{
    auto result = listen("Daqc");
    if (result)
        qDebug()<<"Daqc server started";
    else 
        qCritical()<<"Daqc server started failed";
}

HandleReceiveMessageTask *DaqcServer::generateHandleRequestTask(const QByteArray& data)
{
    return new DaqcServerHandleReceiveMessageTask(this, data);
}
