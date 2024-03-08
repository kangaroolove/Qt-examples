#include "DaqcClientHandleReceiveMessageTask.h"
#include "Client.h"
#include <QJsonDocument>
#include <QJsonObject>

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

    RequestResult result;

    QString clientMessageId = document["clientMessageId"].toString();
    result.value = document["data"].toObject()["value"].toVariant();
    result.valueType = document["data"].toObject()["valueType"].toString();

    m_client->insertRequestResult(clientMessageId, result);
}
