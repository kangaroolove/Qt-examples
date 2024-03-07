#include "DaqcClientHandleReceiveMessageTask.h"
#include "Client.h"
#include <QJsonDocument>

DaqcClientHandleReceiveMessageTask::DaqcClientHandleReceiveMessageTask(Client* client, const QByteArray& data) :
    HandleReceiveMessageTask(data),
    m_client(client)
{

}

DaqcClientHandleReceiveMessageTask::~DaqcClientHandleReceiveMessageTask()
{

}

void DaqcClientHandleReceiveMessageTask::analyzeJson(const QByteArray &data)
{
    auto document = QJsonDocument::fromJson(data);
    if (document.isNull())
        return;
}
