#include "GetValueTask.h"
#include "ReplyPacket.h"
#include "SendTask.h"
#include "Server.h"
#include <QThreadPool>

GetValueTask::GetValueTask(Server* server, const QString& parameter, const QString& clientMessageId) :
    m_parameter(parameter),
    m_clientMessageId(clientMessageId),
    m_server(server)
{

}

GetValueTask::~GetValueTask()
{

}

void GetValueTask::run()
{
    ReplyPacketInfo replyPacketInfo;
    replyPacketInfo.parameter = m_parameter;
    replyPacketInfo.clientMessageId = m_clientMessageId;
    replyPacketInfo.requestType = "get";

    if (replyPacketInfo.parameter == "test")
    {
        replyPacketInfo.value = QVariant(10);
        replyPacketInfo.valueType = "int";
    }

    ReplyPacket* packet = new ReplyPacket(replyPacketInfo);
    auto task = new SendTask(packet);
    QObject::connect(task, &SendTask::sendMessage, m_server, &Server::sendMessage, Qt::QueuedConnection);
    QThreadPool::globalInstance()->start(task);
}
