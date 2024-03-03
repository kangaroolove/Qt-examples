#include "DaqcHandleRequestTask.h"
#include <QJsonDocument>

DaqcHandleRequestTask::DaqcHandleRequestTask(const QByteArray& data) :
    HandleRequestTask(data)
{

}

DaqcHandleRequestTask::~DaqcHandleRequestTask()
{

}

void DaqcHandleRequestTask::analyzeJson(const QByteArray &data)
{
    auto document = QJsonDocument::fromJson(data);
    if (document.isNull())
        return;

    QString api = document["api"].toString();
    handleTask(api);
}

void DaqcHandleRequestTask::handleTask(const QString &api)
{
}
