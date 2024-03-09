#include "DaqcClient.h"
#include "RequestGetPacket.h"
#include "RequestUpdatePacket.h"
#include "Client.h"
#include "ParameterDef.h"
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
        return new RequestGetPacket(REGION_PHYSICAL_DELTA_X);
    });
    return result.toDouble();
}

double DaqcClient::getRegionPhysicalDeltaY()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(REGION_PHYSICAL_DELTA_Y);
    });
    return result.toDouble();
}

int DaqcClient::getBGain()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(B_GAIN);
    });
    return result.toInt();
}

int DaqcClient::getCGain()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(C_GAIN);
    });
    return result.toInt();
}

int DaqcClient::getMGain()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(M_GAIN);
    });
    return result.toInt();
}

double DaqcClient::getXmlDepth()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(XML_DEPTH);
    });
    return result.toDouble();
}

int DaqcClient::getDepthMm()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DEPTH_MM);
    });
    return result.toInt();
}

double DaqcClient::getDepthCm()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DEPTH_CM);
    });
    return result.toDouble();
}

double DaqcClient::getBFrequency()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(B_FREQUENCY);
    });
    return result.toDouble();
}

double DaqcClient::getBFrequency2()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(B_FREQUENCY_2);
    });
    return result.toDouble();
}

double DaqcClient::getMFrequency()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(M_FREQUENCY);
    });
    return result.toDouble();
}

int DaqcClient::getChroma()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(CHROMA);
    });
    return result.toInt();
}

int DaqcClient::getImgProc()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(IMG_PROC);
    });
    return result.toInt();
}

int DaqcClient::getFavg()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(FAVG);
    });
    return result.toInt();
}

int DaqcClient::getLavg()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(LAVG);
    });
    return result.toInt();
}

int DaqcClient::getContrast()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(CONTRAST);
    });
    return result.toInt();
}

double DaqcClient::getCPrf()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(C_PRF);
    });
    return result.toDouble();
}

double DaqcClient::getDPrf()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(D_PRF);
    });
    return result.toDouble();
}

double DaqcClient::getCWf()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(C_WF);
    });
    return result.toDouble();
}

double DaqcClient::getDWf()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(D_WF);
    });
    return result.toDouble();
}

int DaqcClient::getSensitivity()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(SENSITIVITY);
    });
    return result.toInt();
}

int DaqcClient::getSwingAngle()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(SWING_ANGLE);
    });
    return result.toInt();
}

double DaqcClient::getSv()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(SV);
    });
    return result.toDouble();
}

double DaqcClient::getCa()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(CA);
    });
    return result.toDouble();
}

int DaqcClient::getDSpeed()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(D_SPEED);
    });
    return result.toInt();
}

int DaqcClient::getMSpeed()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(M_SPEED);
    });
    return result.toInt();
}

int DaqcClient::getNoiseReject()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(NOISE_REJECT);
    });
    return result.toInt();
}

int DaqcClient::getAudio()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(AUDIO);
    });
    return result.toInt();
}

int DaqcClient::getBaseline()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(BASELINE);
    });
    return result.toInt();
}

int DaqcClient::getRotation()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(ROTATION);
    });
    return result.toInt();
}

double DaqcClient::getSpacingX()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(SPACING_X);
    });
    return result.toDouble();
}

double DaqcClient::getSpacingY()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(SPACING_Y);
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
        return new RequestGetPacket("IsDualModeOn");
    });
    return result.toBool();
}

void DaqcClient::setBGain(bool increase)
{
    createUpdateRequest(new RequestUpdatePacket(B_GAIN, boolToIncrease(increase), "int"));
}

void DaqcClient::setCGain(bool increase)
{
    createUpdateRequest(new RequestUpdatePacket(C_GAIN, boolToIncrease(increase), "int"));
}

void DaqcClient::setMGain(bool increase)
{
    createUpdateRequest(new RequestUpdatePacket(M_GAIN, boolToIncrease(increase), "int"));
}

void DaqcClient::setDepth(bool increase)
{
    createUpdateRequest(new RequestUpdatePacket(DEPTH, boolToIncrease(increase), "int"));
}

void DaqcClient::setBFrequency(bool increase)
{
    createUpdateRequest(new RequestUpdatePacket(B_FREQUENCY, boolToIncrease(increase), "int"));
}

void DaqcClient::setBFrequency2(bool increase)
{
    createUpdateRequest(new RequestUpdatePacket(B_FREQUENCY_2, boolToIncrease(increase), "int"));
}

void DaqcClient::setMFrequency(bool increase)
{
    createUpdateRequest(new RequestUpdatePacket(M_FREQUENCY, boolToIncrease(increase), "int"));
}

void DaqcClient::setChroma(bool increase)
{
    createUpdateRequest(new RequestUpdatePacket(CHROMA, boolToIncrease(increase), "int"));
}

void DaqcClient::setImgProc(bool increase, const std::vector<int> &params)
{
    createUpdateRequest(new RequestUpdatePacket(IMG_PROC, boolToIncrease(increase), "int"));
}

void DaqcClient::setFavg(bool increase)
{
    createUpdateRequest(new RequestUpdatePacket(FAVG, boolToIncrease(increase), "int"));
}

void DaqcClient::setLavg(bool increase)
{
    createUpdateRequest(new RequestUpdatePacket(LAVG, boolToIncrease(increase), "int"));
}

void DaqcClient::setContrast(bool increase)
{
    createUpdateRequest(new RequestUpdatePacket(CONTRAST, boolToIncrease(increase), "int"));
}

void DaqcClient::setCPrf(bool increase)
{
    createUpdateRequest(new RequestUpdatePacket(C_PRF, boolToIncrease(increase), "int"));
}

void DaqcClient::setDPrf(bool increase)
{
    createUpdateRequest(new RequestUpdatePacket(D_PRF, boolToIncrease(increase), "int"));
}

void DaqcClient::setCWf(bool increase)
{
    createUpdateRequest(new RequestUpdatePacket(C_WF, boolToIncrease(increase), "int"));
}

void DaqcClient::setDWf(bool increase)
{
    createUpdateRequest(new RequestUpdatePacket(D_WF, boolToIncrease(increase), "int"));
}

void DaqcClient::setSensitivity(bool increase)
{
    createUpdateRequest(new RequestUpdatePacket(SENSITIVITY, boolToIncrease(increase), "int"));
}

void DaqcClient::setSwingAngle(bool increase)
{
    createUpdateRequest(new RequestUpdatePacket(SWING_ANGLE, boolToIncrease(increase), "int"));
}

void DaqcClient::setSv(bool increase)
{
    createUpdateRequest(new RequestUpdatePacket(SV, boolToIncrease(increase), "int"));
}

void DaqcClient::setCa(bool increase)
{
    createUpdateRequest(new RequestUpdatePacket(CA, boolToIncrease(increase), "int"));
}

void DaqcClient::setDSpeed(bool increase)
{
    createUpdateRequest(new RequestUpdatePacket(D_SPEED, boolToIncrease(increase), "int"));
}

void DaqcClient::setMSpeed(bool increase)
{
    createUpdateRequest(new RequestUpdatePacket(M_SPEED, boolToIncrease(increase), "int"));
}

void DaqcClient::setNoiseReject(bool increase)
{
    createUpdateRequest(new RequestUpdatePacket(NOISE_REJECT, boolToIncrease(increase), "int"));
}

void DaqcClient::setAudio(bool increase)
{
    createUpdateRequest(new RequestUpdatePacket(AUDIO, boolToIncrease(increase), "int"));
}

void DaqcClient::setBaseline(bool increase)
{
    createUpdateRequest(new RequestUpdatePacket(BASELINE, boolToIncrease(increase), "int"));
}

void DaqcClient::setRotation(bool increase)
{
    createUpdateRequest(new RequestUpdatePacket(ROTATION, boolToIncrease(increase), "int"));
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

int DaqcClient::boolToIncrease(const bool &increase)
{
    return increase ? 1 : -1;
}
