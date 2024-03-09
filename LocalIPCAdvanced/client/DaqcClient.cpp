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
        return new RequestGetPacket("RegionPhysicalDeltaX");
    });
    return result.toDouble();
}

double DaqcClient::getRegionPhysicalDeltaY()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("RegionPhysicalDeltaY");
    });
    return result.toDouble();
}

int DaqcClient::getBGain()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("BGain");
    });
    return result.toInt();
}

int DaqcClient::getCGain()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("CGain");
    });
    return result.toInt();
}

int DaqcClient::getMGain()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("MGain");
    });
    return result.toInt();
}

double DaqcClient::getXmlDepth()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("XmlDepth");
    });
    return result.toDouble();
}

int DaqcClient::getDepthMm()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("DepthMm");
    });
    return result.toInt();
}

double DaqcClient::getDepthCm()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("DepthCm");
    });
    return result.toDouble();
}

double DaqcClient::getBFrequency()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("BFrequency");
    });
    return result.toDouble();
}

double DaqcClient::getBFrequency2()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("BFrequency2");
    });
    return result.toDouble();
}

double DaqcClient::getMFrequency()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("MFrequency");
    });
    return result.toDouble();
}

int DaqcClient::getChroma()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("Chroma");
    });
    return result.toInt();
}

int DaqcClient::getImgProc()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("ImgProc");
    });
    return result.toInt();
}

int DaqcClient::getFavg()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("Favg");
    });
    return result.toInt();
}

int DaqcClient::getLavg()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("Lavg");
    });
    return result.toInt();
}

int DaqcClient::getContrast()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("Contrast");
    });
    return result.toInt();
}

double DaqcClient::getCPrf()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("CPrf");
    });
    return result.toDouble();
}

double DaqcClient::getDPrf()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("DPrf");
    });
    return result.toDouble();
}

double DaqcClient::getCWf()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("CWf");
    });
    return result.toDouble();
}

double DaqcClient::getDWf()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("DWf");
    });
    return result.toDouble();
}

int DaqcClient::getSensitivity()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("Sensitivity");
    });
    return result.toInt();
}

int DaqcClient::getSwingAngle()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("SwingAngle");
    });
    return result.toInt();
}

double DaqcClient::getSv()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("Sv");
    });
    return result.toDouble();
}

double DaqcClient::getCa()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("Ca");
    });
    return result.toDouble();
}

int DaqcClient::getDSpeed()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("DSpeed");
    });
    return result.toInt();
}

int DaqcClient::getMSpeed()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("MSpeed");
    });
    return result.toInt();
}

int DaqcClient::getNoiseReject()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("NoiseReject");
    });
    return result.toInt();
}

int DaqcClient::getAudio()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("Audio");
    });
    return result.toInt();
}

int DaqcClient::getBaseline()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("Baseline");
    });
    return result.toInt();
}

int DaqcClient::getRotation()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("Rotation");
    });
    return result.toInt();
}

double DaqcClient::getSpacingX()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("SpacingX");
    });
    return result.toDouble();
}

double DaqcClient::getSpacingY()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("SpacingY");
    });
    return result.toDouble();
}

bool DaqcClient::isBb()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("IsBb");
    });
    return result.toBool();
}

bool DaqcClient::isUp()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("IsUp");
    });
    return result.toBool();
}

bool DaqcClient::isThi()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("IsThi");
    });
    return result.toBool();
}

bool DaqcClient::isCenterLine()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("IsCenterLine");
    });
    return result.toBool();
}

bool DaqcClient::isRoiSite()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("IsRoiSite");
    });
    return result.toBool();
}

bool DaqcClient::isRoiSize()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("IsRoiSize");
    });
    return result.toBool();
}

bool DaqcClient::isCInvert()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("IsCInvert");
    });
    return result.toBool();
}

bool DaqcClient::isDInvert()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("IsDInvert");
    });
    return result.toBool();
}

bool DaqcClient::isCAutoTrace()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("IsCAutoTrace");
    });
    return result.toBool();
}

bool DaqcClient::isDAutoTrace()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("IsDAutoTrace");
    });
    return result.toBool();
}

bool DaqcClient::isUpdate()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("IsUpdate");
    });
    return result.toBool();
}

bool DaqcClient::isSynchro()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("IsSynchro");
    });
    return result.toBool();
}

QPoint DaqcClient::getRoiPosition()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("RoiPosition");
    });
    return result.toPoint();
}

int DaqcClient::getDualConvexOrLinearChannel()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("DualConvexOrLinearChannel");
    });
    return result.toInt();
}

bool DaqcClient::isDualModeOn()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket("DualModeOn");
    });
    return result.toBool();
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
