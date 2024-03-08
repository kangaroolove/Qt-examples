#include "DaqcClient.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QUuid>

DaqcClient::DaqcClient(QObject* parent) :
    Client(parent)
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



    // QJsonObject rootObject;
    // QJsonObject object;
    // object["parameter"] = "testApi";
    // object["requestType"] = "get";

    // rootObject["data"] = object;
    // rootObject["messageId"] = messageId;
    // QJsonDocument document(rootObject);



    // sendMessage(document.toJson(QJsonDocument::Compact));

    // QEventLoop* eventLoop = new QEventLoop(this);
    // m_eventLoopMap.insert({messageId, eventLoop});
    // eventLoop->exec();

    return 0;
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
