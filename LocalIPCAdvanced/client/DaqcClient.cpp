#include "DaqcClient.h"
#include "SendTask.h"
#include "RequestGetTest.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QThreadPool>
#include <QEventLoop>

DaqcClient::DaqcClient(QObject* parent) :
    Client(parent),
{

}

DaqcClient::~DaqcClient()
{

}

void DaqcClient::start()
{
    connectToServer("Daqc");
    qDebug()<<"Connect to server";
}

int DaqcClient::testGetApi()
{
    auto packet = new RequestGetTest;
    QThreadPool::globalInstance()->start(new SendTask(this, packet));

    QEventLoop* eventLoop = new QEventLoop(this);
    m_eventLoopMap.insert({packet->getMessageId(), eventLoop});
    eventLoop->exec();

    RequestResult result = getRequestResult(packet->getMessageId());
    if (result.valueType == "int")
        return result.value.toInt();
}

void DaqcClient::testSetApi(bool isTest)
{
    // QString messageId = QUuid::createUuid().toString();
    // QJsonObject object;
    // object["api"] = "testSetApi";
    // object["value"] = 10;
    // object["type"] = "int";
    // QJsonDocument document(object);
    // sendMessage(document.toJson(QJsonDocument::Compact));
}
