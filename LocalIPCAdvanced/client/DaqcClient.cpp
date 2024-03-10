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

void DaqcClient::setBGainValue(int value)
{
    createUpdateRequest(new RequestUpdatePacket(B_GAIN, value, "int"));
}

void DaqcClient::setDepthValue(int value)
{
    createUpdateRequest(new RequestUpdatePacket(DEPTH, value, "int"));
}

void DaqcClient::setBFrequencyValue(double value)
{
    createUpdateRequest(new RequestUpdatePacket(B_FREQUENCY, value, "double"));
}

void DaqcClient::setChromaValue(int value)
{
    createUpdateRequest(new RequestUpdatePacket(CHROMA, value, "int"));
}

void DaqcClient::setImgProcValue(int value, const std::vector<int> &params)
{
    createUpdateRequest(new RequestUpdatePacket(CHROMA, value, "vector<int>"));
}

void DaqcClient::setFavgValue(int value)
{
    createUpdateRequest(new RequestUpdatePacket(FAVG, value, "int"));
}

void DaqcClient::setLavgValue(int value)
{
    createUpdateRequest(new RequestUpdatePacket(LAVG, value, "int"));
}

void DaqcClient::setContrastValue(int value)
{
    createUpdateRequest(new RequestUpdatePacket(CONTRAST, value, "int"));
}

void DaqcClient::setRotationValue(int value)
{
    createUpdateRequest(new RequestUpdatePacket(ROTATION, value, "int"));
}

void DaqcClient::setBb(bool value)
{

}

void DaqcClient::setUp(bool value)
{
}

void DaqcClient::setThi(bool value)
{
}

void DaqcClient::setCenterLine(bool value)
{

}

void DaqcClient::setRoiSite(bool value)
{
    createUpdateRequest(new RequestUpdatePacket(ROI_SITE, value, "bool"));
}

void DaqcClient::setRoiSize(bool value)
{
    createUpdateRequest(new RequestUpdatePacket(ROI_SIZE, value, "bool"));
}

void DaqcClient::setCInvert(bool value)
{
    createUpdateRequest(new RequestUpdatePacket(C_INVERT, value, "bool"));
}

void DaqcClient::setDInvert(bool value)
{
    createUpdateRequest(new RequestUpdatePacket(D_INVERT, value, "bool"));
}

void DaqcClient::setCAutoTrace(bool value)
{
    createUpdateRequest(new RequestUpdatePacket(C_AUTO_TRACE, value, "bool"));
}

void DaqcClient::setDAutoTrace(bool value)
{
    createUpdateRequest(new RequestUpdatePacket(D_AUTO_TRACE, value, "bool"));
}

void DaqcClient::setUpdate(bool value)
{
    createUpdateRequest(new RequestUpdatePacket(UPDATE, value, "bool"));
}

void DaqcClient::setSynchro(bool value)
{
    createUpdateRequest(new RequestUpdatePacket(SYNCHRO, value, "bool"));
}

void DaqcClient::setDualMode(bool value)
{
    createUpdateRequest(new RequestUpdatePacket(DUAL_MODE, value, "bool"));
}

void DaqcClient::cancelRoi()
{
}

int DaqcClient::legacyACUI()
{
    return 0;
}

void DaqcClient::legacySetACUI(int value)
{
}

int DaqcClient::legacyAPower()
{
    return 0;
}

void DaqcClient::legacySetAPower(int value)
{
}

int DaqcClient::legacyAnatomyLine()
{
    return 0;
}

void DaqcClient::legacySetAnatomyLine(int value)
{
}

int DaqcClient::legacyBCDSynChro()
{
    return 0;
}

void DaqcClient::legacySetBCDSynChro(int value)
{
}

int DaqcClient::legacyBDynamic()
{
    return 0;
}

void DaqcClient::legacySetBDynamic(int value)
{
}

int DaqcClient::legacyBGain()
{
    return 0;
}

void DaqcClient::legacySetBGain(int value)
{
}

int DaqcClient::legacyBGain2()
{
    return 0;
}

void DaqcClient::legacySetBGain2(int value)
{
}

int DaqcClient::legacyBNoiseRej()
{
    return 0;
}

void DaqcClient::legacySetBNoiseRej(int value)
{
}

int DaqcClient::legacyCBaseLine()
{
    return 0;
}

void DaqcClient::legacySetCBaseLine(int value)
{
}

int DaqcClient::legacyCDynamic()
{
    return 0;
}

void DaqcClient::legacySetCDynamic(int value)
{
}

double DaqcClient::legacyCFreq()
{
    return 0.0;
}

void DaqcClient::legacySetCFreq(double value)
{
}

int DaqcClient::legacyCGain()
{
    return 0;
}

void DaqcClient::legacySetCGain(int value)
{
}

int DaqcClient::legacyCNoiseRej()
{
    return 0;
}

void DaqcClient::legacySetCNoiseRej(int value)
{
}

double DaqcClient::legacyCPRF()
{
    return 0.0;
}

void DaqcClient::legacySetCPRF(double value)
{
}

double DaqcClient::legacyCWallFilterFreq()
{
    return 0.0;
}

void DaqcClient::legacySetCWallFilterFreq(double value)
{
}

bool DaqcClient::legacyColorInvert()
{
    return false;
}

void DaqcClient::legacySetColorInvert(bool value)
{
}

int DaqcClient::legacyColorPrior()
{
    return 0;
}

void DaqcClient::legacySetColorPrior(int value)
{
}

int DaqcClient::legacyCwdGain()
{
    return 0;
}

void DaqcClient::legacySetCwdGain(int value)
{
}

int DaqcClient::legacyDBaseLine()
{
    return 0;
}

void DaqcClient::legacySetDBaseLine(int value)
{
}

int DaqcClient::legacyDDynamic()
{
    return 0;
}

void DaqcClient::legacySetDDynamic(int value)
{
}

int DaqcClient::legacyDNoiseRej()
{
    return 0;
}

void DaqcClient::legacySetDNoiseRej(int value)
{
}

double DaqcClient::legacyDPRF()
{
    return 0.0;
}

void DaqcClient::legacySetDPRF(double value)
{
}

int DaqcClient::legacyDSoundVolum()
{
    return 0;
}

void DaqcClient::legacySetDSoundVolum(int value)
{
}

int DaqcClient::legacyDSpeed()
{
    return 0;
}

void DaqcClient::legacySetDSpeed(int value)
{
}

double DaqcClient::legacyDWallFilterFreq()
{
    return 0.0;
}

void DaqcClient::legacySetDWallFilterFreq(double value)
{
}

int DaqcClient::legacyDepth()
{
    return 0;
}

void DaqcClient::legacySetDepth(int value)
{
}

int DaqcClient::legacyDirPwrGain()
{
    return 0;
}

void DaqcClient::legacySetDirPwrGain(int value)
{
}

int DaqcClient::legacyDscCapture()
{
    return 0;
}

void DaqcClient::legacySetDscCapture(int value)
{
}

int DaqcClient::legacyExamTypeID()
{
    return 0;
}

void DaqcClient::legacySetExamTypeID(int value)
{
}

double DaqcClient::legacyFrameRelation()
{
    return 0.0;
}

void DaqcClient::legacySetFrameRelation(double value)
{
}

double DaqcClient::legacyFreq2()
{
    return 0.0;
}

void DaqcClient::legacySetFreq2(double value)
{
}

double DaqcClient::legacyFrequence()
{
    return 0.0;
}

void DaqcClient::legacySetFrequence(double value)
{
}

int DaqcClient::legacyGetDscStop()
{
    return 0;
}

void DaqcClient::legacySetGetDscStop(int value)
{
}

int DaqcClient::legacyImageProcess()
{
    return 0;
}

void DaqcClient::legacySetImageProcess(int value)
{
}

int DaqcClient::legacyLavgRelation()
{
    return 0;
}

void DaqcClient::legacySetLavgRelation(int value)
{
}

int DaqcClient::legacyLineDensity()
{
    return 0;
}

void DaqcClient::legacySetLineDensity(int value)
{
}

int DaqcClient::legacyMGain()
{
    return 0;
}

void DaqcClient::legacySetMGain(int value)
{
}

double DaqcClient::legacyMSpeed()
{
    return 0.0;
}

void DaqcClient::legacySetMSpeed(double value)
{
}

int DaqcClient::legacyPWDCompress()
{
    return 0;
}

void DaqcClient::legacySetPWDCompress(int value)
{
}

double DaqcClient::legacyPWDCorrectionAngle()
{
    return 0.0;
}

void DaqcClient::legacySetPWDCorrectionAngle(double value)
{
}

double DaqcClient::legacyPWDgateSize()
{
    return 0.0;
}

void DaqcClient::legacySetPWDgateSize(double value)
{
}

double DaqcClient::legacyPWDsampleDepth()
{
    return 0.0;
}

void DaqcClient::legacySetPWDsampleDepth(double value)
{
}

int DaqcClient::legacyPWDstartPos()
{
    return 0;
}

void DaqcClient::legacySetPWDstartPos(int value)
{
}

int DaqcClient::legacyPersistenceColor()
{
    return 0;
}

void DaqcClient::legacySetPersistenceColor(int value)
{
}

int DaqcClient::legacyProbePOS()
{
    return 0;
}

void DaqcClient::legacySetProbePOS(int value)
{
}

int DaqcClient::legacyProbeSEL()
{
    return 0;
}

void DaqcClient::legacySetProbeSEL(int value)
{
}

int DaqcClient::legacyPwdGain()
{
    return 0;
}

void DaqcClient::legacySetPwdGain(int value)
{
}

bool DaqcClient::legacyPwdInvert()
{
    return false;
}

void DaqcClient::legacySetPwdInvert(bool value)
{
}

int DaqcClient::legacyPwrGain()
{
    return 0;
}

void DaqcClient::legacySetPwrGain(int value)
{
}

int DaqcClient::legacyPwrMode()
{
    return 0;
}

void DaqcClient::legacySetPwrMode(int value)
{
}

int DaqcClient::legacyROISwingAngle()
{
    return 0;
}

void DaqcClient::legacySetROISwingAngle(int value)
{
}

double DaqcClient::legacyRadium()
{
    return 0.0;
}

void DaqcClient::legacySetRadium(double value)
{
}

int DaqcClient::legacyResetProbe()
{
    return 0;
}

void DaqcClient::legacySetResetProbe(int value)
{
}

int DaqcClient::legacyScanLine()
{
    return 0;
}

void DaqcClient::legacySetScanLine(int value)
{
}

int DaqcClient::legacyTHI()
{
    return 0;
}

void DaqcClient::legacySetTHI(int value)
{
}

int DaqcClient::legacyZoomImg()
{
    return 0;
}

void DaqcClient::legacySetZoomImg(int value)
{
}

int DaqcClient::legacyBFocusLch()
{
    return 0;
}

void DaqcClient::legacySetBFocusLch(int value)
{
}

int DaqcClient::legacyCAutoTrace()
{
    return 0;
}

void DaqcClient::legacySetCAutoTrace(int value)
{
}

int DaqcClient::legacyCFocusLch()
{
    return 0;
}

void DaqcClient::legacySetCFocusLch(int value)
{
}

double DaqcClient::legacyESpin()
{
    return 0.0;
}

void DaqcClient::legacySetESpin(double value)
{
}

int DaqcClient::legacyImgExtend()
{
    return 0;
}

void DaqcClient::legacySetImgExtend(int value)
{
}

int DaqcClient::legacyPosNeg()
{
    return 0;
}

void DaqcClient::legacySetPosNeg(int value)
{
}

int DaqcClient::legacyPwifBuffms()
{
    return 0;
}

void DaqcClient::legacySetPwifBuffms(int value)
{
}

int DaqcClient::legacyScanFeature()
{
    return 0;
}

void DaqcClient::legacySetScanFeature(int value)
{
}

int DaqcClient::legacyScanMode()
{
    return 0;
}

void DaqcClient::legacySetScanMode(int value)
{
}

int DaqcClient::legacySmooth()
{
    return 0;
}

void DaqcClient::legacySetSmooth(int value)
{
}

void DaqcClient::legacyAboutBox()
{
}

void DaqcClient::legacyFacuiParams(int pXh, int vAcui)
{
}

void DaqcClient::legacyGetColorDopplerROI(int startPos, int endPos, int startDepth, int endDepth)
{
}

int DaqcClient::legacyGetDepthSf()
{
    return 0;
}

double DaqcClient::legacyGetFPS()
{
    return 0.0;
}

double DaqcClient::legacyGetParameter(int id)
{
    return 0.0;
}

int DaqcClient::legacyGetProbeInfo(int id)
{
    return 0;
}

void DaqcClient::legacyGetTGCPositions(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8)
{
}

void DaqcClient::legacyInit(int inum)
{
}

void DaqcClient::legacyMode2B()
{
}

void DaqcClient::legacyMode4B(int wid)
{
}

void DaqcClient::legacyMoveColorROI(int LeftRight, int UpDown)
{
}

void DaqcClient::legacyMoveROIColor(int x, int y)
{
}

void DaqcClient::legacyPalette(int colorID, int bright, int ts)
{
}

void DaqcClient::legacyRealtimeEn(int en)
{
}

void DaqcClient::legacySetColorDopplerROI(int startPos, int endPos, int startDepth, int endDepth)
{
}

void DaqcClient::legacySetFlipH(int isFlip)
{
}

void DaqcClient::legacySetFlipV(int isFlip)
{
}

void DaqcClient::legacySetPwdAutoTrace(int nAuto)
{
}

void DaqcClient::legacySetTGCPositions(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8)
{
}

void DaqcClient::legacySetiClear(int id)
{
}

void DaqcClient::legacyZoomColorROI(int xDirection, int yDirection)
{
}

void DaqcClient::legacyFProbeType(int pbPort, int pbType)
{
}

void DaqcClient::legacySaveScuInitPara()
{
}

void DaqcClient::legacyStart()
{
}

void DaqcClient::legacyStop()
{
}

void DaqcClient::legacyWifiEWM(const QString &fptStr, QString &htpStr)
{
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
