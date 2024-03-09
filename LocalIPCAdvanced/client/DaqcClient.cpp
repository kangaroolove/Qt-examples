#include "DaqcClient.h"
#include "RequestGetPacket.h"
#include "RequestUpdatePacket.h"
#include "Client.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QThreadPool>
#include <QEventLoop>

DaqcClient::DaqcClient(QObject* parent) :
    m_client(new Client()),
    m_thread(new QThread(this))
{
    m_client->moveToThread(m_thread);
    connect(m_thread, &QThread::finished, m_client, &Client::deleteLater);
    connect(this, &DaqcClient::sendMessage, m_client, &Client::sendMessage);
    connect(this, &DaqcClient::connectServer, m_client, &Client::connectServer);
    connect(m_client, &Client::receiveMessage, this, &DaqcClient::receiveMessage);
    m_thread->start();
}

DaqcClient::~DaqcClient()
{
    m_thread->quit();
    m_thread->wait();
}

void DaqcClient::start()
{
    emit connectServer();
    qDebug()<<"Connect to server";
}

int DaqcClient::testGetApi()
{
    auto result = createGetRequest([]{ 
        return new RequestGetPacket("test"); 
    });
    return result.toInt();
}

void DaqcClient::testSetApi(bool isTest)
{
    createUpdateRequest(new RequestUpdatePacket("test", isTest, "bool"));
}

double DaqcClient::getRegionPhysicalDeltaX()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("regionPhysicalDeltaX");
    });
    return result.toDouble();
}

double DaqcClient::getRegionPhysicalDeltaY()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("regionPhysicalDeltaY");
    });
    return result.toDouble();
}

int DaqcClient::getBGain()
{
    return 0;
}

int DaqcClient::getCGain()
{
    return 0;
}

int DaqcClient::getMGain()
{
    return 0;
}

double DaqcClient::getXmlDepth()
{
    return 0.0;
}

int DaqcClient::getDepthMm()
{
    return 0;
}

double DaqcClient::getDepthCm()
{
    return 0.0;
}

double DaqcClient::getBFrequency()
{
    return 0.0;
}

double DaqcClient::getBFrequency2()
{
    return 0.0;
}

double DaqcClient::getMFrequency()
{
    return 0.0;
}

int DaqcClient::getChroma()
{
    return 0;
}

int DaqcClient::getImgProc()
{
    return 0;
}

int DaqcClient::getFavg()
{
    return 0;
}

int DaqcClient::getLavg()
{
    return 0;
}

int DaqcClient::getContrast()
{
    return 0;
}

double DaqcClient::getCPrf()
{
    return 0.0;
}

double DaqcClient::getDPrf()
{
    return 0.0;
}

double DaqcClient::getCWf()
{
    return 0.0;
}

double DaqcClient::getDWf()
{
    return 0.0;
}

int DaqcClient::getSensitivity()
{
    return 0;
}

int DaqcClient::getSwingAngle()
{
    return 0;
}

double DaqcClient::getSv()
{
    return 0.0;
}

double DaqcClient::getCa()
{
    return 0.0;
}

int DaqcClient::getDSpeed()
{
    return 0;
}

int DaqcClient::getMSpeed()
{
    return 0;
}

int DaqcClient::getNoiseReject()
{
    return 0;
}

int DaqcClient::getAudio()
{
    return 0;
}

int DaqcClient::getBaseline()
{
    return 0;
}

int DaqcClient::getRotation()
{
    return 0;
}

double DaqcClient::getSpacingX()
{
    return 0.0;
}

double DaqcClient::getSpacingY()
{
    return 0.0;
}

bool DaqcClient::isBb()
{
    return false;
}

bool DaqcClient::isUp()
{
    return false;
}

bool DaqcClient::isThi()
{
    return false;
}

bool DaqcClient::isCenterLine()
{
    return false;
}

bool DaqcClient::isRoiSite()
{
    return false;
}

bool DaqcClient::isRoiSize()
{
    return false;
}

bool DaqcClient::isCInvert()
{
    return false;
}

bool DaqcClient::isDInvert()
{
    return false;
}

bool DaqcClient::isCAutoTrace()
{
    return false;
}

bool DaqcClient::isDAutoTrace()
{
    return false;
}

bool DaqcClient::isUpdate()
{
    return false;
}

bool DaqcClient::isSynchro()
{
    return false;
}

QPoint DaqcClient::getRoiPosition()
{
    return QPoint();
}

int DaqcClient::getDualConvexOrLinearChannel()
{
    return 0;
}

bool DaqcClient::isDualModeOn()
{
    return false;
}

QVariant DaqcClient::createGetRequest(std::function<Packet*()> callback)
{
    QEventLoop eventloop;
    connect(m_client, &Client::quitEventloop, &eventloop, &QEventLoop::quit);

    Packet* packet = callback();
    emit sendMessage(packet->toJson());
    eventloop.exec();

    RequestResult result = m_client->getRequestResult(packet->getMessageId());
    packet->deleteLater();
    return result.value;
}

void DaqcClient::createUpdateRequest(Packet *packet)
{
    emit sendMessage(packet->toJson());
    packet->deleteLater();
}
