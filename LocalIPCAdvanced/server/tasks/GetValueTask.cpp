#include "GetValueTask.h"
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
    ReplyPacket* packet = new ReplyPacket(getReplyPacketInfo());
    auto task = new SendTask(packet);
    // Since server is created by main thread, so we need to use QueuedConnection
    QObject::connect(task, &SendTask::sendMessage, m_server, &Server::sendMessage, Qt::QueuedConnection);
    QThreadPool::globalInstance()->start(task);
}

ReplyPacketInfo GetValueTask::getReplyPacketInfo()
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

    return replyPacketInfo;
}
