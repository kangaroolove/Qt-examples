#include "DaqcClient.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

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
}

void DaqcClient::testGetApi()
{
    QJsonObject object;
    object["api"] = "testGetApi";
    QJsonDocument document(object);
    sendMessage(document.toJson());
}

void DaqcClient::testSetApi(bool isTest)
{
}
