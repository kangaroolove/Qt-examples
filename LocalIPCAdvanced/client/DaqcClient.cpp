#include "DaqcClient.h"
#include "RequestGetPacket.h"
#include "RequestUpdatePacket.h"
#include "Client.h"
#include "StringDef.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QThreadPool>
#include <QEventLoop>
#include <QImage>

DaqcClient::DaqcClient(QObject* parent) :
    Client(parent)
{
}

DaqcClient::~DaqcClient()
{
}

void DaqcClient::start()
{
    m_worker->connectToServer("Daqc");
    qDebug()<<"Connect to server";
}

int DaqcClient::testGetApi()
{
    auto result = createGetRequest([]{ 
        QVariantList values = { 50 };
        QStringList valueTypes = { "int" };
        return new RequestGetPacket("test", values, valueTypes); 
    });

    return result.toInt();
}

void DaqcClient::testSetApi(bool isTest)
{
    QVariantList values = { true };
    createUpdateRequest(new RequestUpdatePacket("test", values, {"bool"}));
}

bool DaqcClient::isConnected()
{
    return false;
}

double DaqcClient::getRegionPhysicalDeltaX()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DaqcParameter::REGION_PHYSICAL_DELTA_X);
    });
    return result.toDouble();
}

double DaqcClient::getRegionPhysicalDeltaY()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DaqcParameter::REGION_PHYSICAL_DELTA_Y);
    });
    return result.toDouble();
}

int DaqcClient::getBGain()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DaqcParameter::B_GAIN);
    });
    return result.toInt();
}

int DaqcClient::getCGain()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DaqcParameter::C_GAIN);
    });
    return result.toInt();
}

double DaqcClient::getXmlDepth()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DaqcParameter::XML_DEPTH);
    });
    return result.toDouble();
}

int DaqcClient::getDepthMm()
{
    return depthHardCode(getXmlDepth());
}

double DaqcClient::getDepthCm()
{
    return mmToCm(getDepthMm());
}

double DaqcClient::getBFrequency()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DaqcParameter::B_FREQUENCY);
    });
    return result.toDouble();
}

double DaqcClient::getBFrequency2()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DaqcParameter::B_FREQUENCY_2);
    });
    return result.toDouble();
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
    // original interface return double
    auto result = createGetRequest([]{
        return new RequestGetPacket(DaqcParameter::FAVG);
    });
    return result.toInt();
}

int DaqcClient::getLavg()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DaqcParameter::LAVG);
    });
    return result.toInt();
}

int DaqcClient::getContrast()
{
    return legacyBDynamic();
}

double DaqcClient::getCPrf()
{
    return legacyCPRF();
}

double DaqcClient::getDPrf()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DaqcParameter::D_PRF);
    });
    return result.toDouble();
}

double DaqcClient::getCWf()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DaqcParameter::C_WF);
    });
    return result.toDouble();
}

double DaqcClient::getDWf()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DaqcParameter::D_WF);
    });
    return result.toDouble();
}

int DaqcClient::getSensitivity()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DaqcParameter::SENSITIVITY);
    });
    return result.toInt();
}

int DaqcClient::getSwingAngle()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DaqcParameter::SWING_ANGLE);
    });
    return result.toInt();
}

double DaqcClient::getSv()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DaqcParameter::SV);
    });
    return result.toDouble();
}

double DaqcClient::getCa()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DaqcParameter::CA);
    });
    return result.toDouble();
}

int DaqcClient::getDSpeed()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DaqcParameter::D_SPEED);
    });
    return result.toInt();
}

int DaqcClient::getNoiseReject()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DaqcParameter::NOISE_REJECT);
    });
    return result.toInt();
}

int DaqcClient::getAudio()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DaqcParameter::AUDIO);
    });
    return result.toInt();
}

int DaqcClient::getRotation()
{
    return 0;
}

double DaqcClient::getSpacingX()
{
    return legacyGetParameter(102);
}

double DaqcClient::getSpacingY()
{
    return legacyGetParameter(103);
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
    return legacyTHI() == 1;
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
    return legacyColorInvert();
}

bool DaqcClient::isDInvert()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DaqcParameter::D_INVERT);
    });
    return result.toBool();
}

bool DaqcClient::isCAutoTrace()
{
    return legacyCAutoTrace() == 1;
}

bool DaqcClient::isDAutoTrace()
{
    return false;
}

bool DaqcClient::isUpdate()
{
    return legacyBCDSynChro() == (int)BcdSynchro::UPDATE;
}

bool DaqcClient::isSynchro()
{
    return legacyBCDSynChro() == (int)BcdSynchro::SYNCHRO;
}

QPoint DaqcClient::getRoiPosition()
{
    return QPoint(0, 0);
}

int DaqcClient::getDualConvexOrLinearChannel()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DaqcParameter::DUAL_CONVEX_OR_LINEAR_CHANNEL);
    });
    return result.toInt();
}

bool DaqcClient::isDualModeOn()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DaqcParameter::DUAL_MODE);
    });
    return result.toBool();
}

void DaqcClient::setBGain(bool increase)
{
    QVariantList values = { boolToIncrease(increase) };
    QStringList valueTypes = { "int" };
    createUpdateRequest(new RequestUpdatePacket(DaqcParameter::B_GAIN, values, valueTypes));
}

void DaqcClient::setCGain(bool increase)
{
    QVariantList values = { boolToIncrease(increase) };
    QStringList valueTypes = { "int" };
    createUpdateRequest(new RequestUpdatePacket(DaqcParameter::C_GAIN, values, valueTypes));
}
#if 0

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
#endif

void DaqcClient::legacySetACUI(int value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "int" };
    createUpdateRequest(new RequestUpdatePacket(DaqcParameter::ACUI, values, valueTypes));
}

int DaqcClient::legacyBCDSynChro()
{
    auto result = createGetRequest([]{ 
        return new RequestGetPacket(DaqcParameter::B_C_D_SYNCHRO); 
    });

    return result.toInt();
}

int DaqcClient::legacyBDynamic()
{
    auto result = createGetRequest([]{ 
        return new RequestGetPacket(DaqcParameter::B_DYNAMIC); 
    });

    return result.toInt();
}

void DaqcClient::legacySetBDynamic(int value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "int" };
    createUpdateRequest(new RequestUpdatePacket(DaqcParameter::B_DYNAMIC, values, valueTypes));
}

int DaqcClient::legacyCBaseLine()
{
    auto result = createGetRequest([]{ 
        return new RequestGetPacket(DaqcParameter::C_BASE_LINE); 
    });

    return result.toInt();
}

double DaqcClient::legacyCPRF()
{
    auto result = createGetRequest([]{ 
        return new RequestGetPacket(DaqcParameter::C_PRF); 
    });

    return result.toDouble();
}

bool DaqcClient::legacyColorInvert()
{
    auto result = createGetRequest([]{ 
        return new RequestGetPacket(DaqcParameter::COLOR_INVERT); 
    });

    return result.toBool();
}

int DaqcClient::legacyDDynamic()
{
    auto result = createGetRequest([]{ 
        return new RequestGetPacket(DaqcParameter::D_DYNAMIC); 
    });

    return result.toInt();
}

void DaqcClient::legacySetDDynamic(int value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "int" };
    createUpdateRequest(new RequestUpdatePacket(DaqcParameter::D_DYNAMIC, values, valueTypes));
}

double DaqcClient::legacyDPRF()
{
    auto result = createGetRequest([]{ 
        return new RequestGetPacket(DaqcParameter::D_PRF); 
    });

    return result.toDouble();
}

void DaqcClient::legacySetExamTypeID(int value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "int" };
    createUpdateRequest(new RequestUpdatePacket(DaqcParameter::EXAM_TYPE_ID, values, valueTypes));
}

void DaqcClient::legacySetImageProcess(int value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "int" };
    createUpdateRequest(new RequestUpdatePacket(DaqcParameter::IMAGE_PROCESS, values, valueTypes));
}

int DaqcClient::legacyPersistenceColor()
{
    auto result = createGetRequest([]{ 
        return new RequestGetPacket(DaqcParameter::PERSISTENCE_COLOR); 
    });

    return result.toInt();
}

void DaqcClient::legacySetPersistenceColor(int value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "int" };
    createUpdateRequest(new RequestUpdatePacket(DaqcParameter::PERSISTENCE_COLOR, values, valueTypes));
}

void DaqcClient::legacySetProbePOS(int value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "int" };
    createUpdateRequest(new RequestUpdatePacket(DaqcParameter::PROBE_POS, values, valueTypes));
}

int DaqcClient::legacyProbeSEL()
{
    auto result = createGetRequest([]{ 
        return new RequestGetPacket(DaqcParameter::PROBE_SEL); 
    });

    return result.toInt();
}

void DaqcClient::legacySetRadium(double value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "double" };
    createUpdateRequest(new RequestUpdatePacket(DaqcParameter::RADIUM, values, valueTypes));
}

int DaqcClient::legacyTHI()
{
    auto result = createGetRequest([]{ 
        return new RequestGetPacket(DaqcParameter::THI); 
    });

    return result.toInt();
}

void DaqcClient::legacySetTHI(int value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "int" };
    createUpdateRequest(new RequestUpdatePacket(DaqcParameter::ESPIN, values, valueTypes));
}

int DaqcClient::legacyCAutoTrace()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DaqcParameter::C_AUTO_TRACE);
    });
    return result.toInt();
}

void DaqcClient::legacySetESpin(double value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "double" };
    createUpdateRequest(new RequestUpdatePacket(DaqcParameter::ESPIN, values, valueTypes));
}

void DaqcClient::legacySetPwifBuffms(int value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "int" };
    createUpdateRequest(new RequestUpdatePacket(DaqcParameter::PWIF_BUFF_MS, values, valueTypes));
}

int DaqcClient::legacyScanMode()
{
    auto result = createGetRequest([]{ 
        return new RequestGetPacket(DaqcParameter::SCAN_MODE); 
    });

    return result.toInt();
}

void DaqcClient::legacySetScanMode(int value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "int" };
    createUpdateRequest(new RequestUpdatePacket(DaqcParameter::SCAN_MODE, values, valueTypes));
}

/*
int DaqcClient::legacyACUI()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(ACUI);
    });
    return result.toDouble();
}

void DaqcClient::legacySetACUI(int value)
{
    createUpdateRequest(new RequestUpdatePacket(ACUI, value, "int"));
}

int DaqcClient::legacyAPower()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(ACUI);
    });
    return result.toDouble();
}

void DaqcClient::legacySetAPower(int value)
{
    createUpdateRequest(new RequestUpdatePacket(A_POWER, value, "int"));
}

int DaqcClient::legacyAnatomyLine()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(ANATOMY_LINE);
    });
    return result.toInt();
}

void DaqcClient::legacySetAnatomyLine(int value)
{
    createUpdateRequest(new RequestUpdatePacket(ANATOMY_LINE, value, "int"));
}

int DaqcClient::legacyBCDSynChro()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(B_C_D_SYNCHRO);
    });
    return result.toInt();
}

void DaqcClient::legacySetBCDSynChro(int value)
{
    createUpdateRequest(new RequestUpdatePacket(ANATOMY_LINE, value, "int"));
}

int DaqcClient::legacyBDynamic()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(B_DYNAMIC);
    });
    return result.toInt();
}

void DaqcClient::legacySetBDynamic(int value)
{
    createUpdateRequest(new RequestUpdatePacket(B_DYNAMIC, value, "int"));
}

int DaqcClient::legacyBGain()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(B_GAIN);
    });
    return result.toInt();
}

void DaqcClient::legacySetBGain(int value)
{
    createUpdateRequest(new RequestUpdatePacket(B_GAIN, value, "int"));
}

int DaqcClient::legacyBGain2()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(B_GAIN2);
    });
    return result.toInt();
}

void DaqcClient::legacySetBGain2(int value)
{
    createUpdateRequest(new RequestUpdatePacket(B_GAIN2, value, "int"));
}

int DaqcClient::legacyBNoiseRej()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(B_NOISE_REJECTION);
    });
    return result.toInt();
}

void DaqcClient::legacySetBNoiseRej(int value)
{
    createUpdateRequest(new RequestUpdatePacket(B_NOISE_REJECTION, value, "int"));
}

int DaqcClient::legacyCBaseLine()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(C_BASE_LINE);
    });
    return result.toInt();
}

void DaqcClient::legacySetCBaseLine(int value)
{
    createUpdateRequest(new RequestUpdatePacket(C_BASE_LINE, value, "int"));
}

int DaqcClient::legacyCDynamic()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(C_DYNAMIC);
    });
    return result.toInt();
}

void DaqcClient::legacySetCDynamic(int value)
{
    createUpdateRequest(new RequestUpdatePacket(C_DYNAMIC, value, "int"));
}

double DaqcClient::legacyCFreq()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(C_FREQUENCY);
    });
    return result.toDouble();
}

void DaqcClient::legacySetCFreq(double value)
{
    createUpdateRequest(new RequestUpdatePacket(C_FREQUENCY, value, "double"));
}

int DaqcClient::legacyCGain()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(C_GAIN);
    });
    return result.toInt();
}

void DaqcClient::legacySetCGain(int value)
{
    createUpdateRequest(new RequestUpdatePacket(C_GAIN, value, "int"));
}

int DaqcClient::legacyCNoiseRej()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(C_NOISE_REJECTION);
    });
    return result.toInt();
}

void DaqcClient::legacySetCNoiseRej(int value)
{
    createUpdateRequest(new RequestUpdatePacket(C_NOISE_REJECTION, value, "int"));
}

double DaqcClient::legacyCPRF()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(C_PRF);
    });
    return result.toDouble();
}

void DaqcClient::legacySetCPRF(double value)
{
    createUpdateRequest(new RequestUpdatePacket(C_PRF, value, "int"));
}

double DaqcClient::legacyCWallFilterFreq()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(C_WALL_FILTER_FREQ);
    });
    return result.toDouble();
}

void DaqcClient::legacySetCWallFilterFreq(double value)
{
    createUpdateRequest(new RequestUpdatePacket(C_WALL_FILTER_FREQ, value, "double"));
}

bool DaqcClient::legacyColorInvert()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(COLOR_INVERT);
    });
    return result.toBool();
}

void DaqcClient::legacySetColorInvert(bool value)
{
    createUpdateRequest(new RequestUpdatePacket(COLOR_INVERT, value, "bool"));
}

int DaqcClient::legacyColorPrior()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(COLOR_PRIOR);
    });
    return result.toInt();
}

void DaqcClient::legacySetColorPrior(int value)
{
    createUpdateRequest(new RequestUpdatePacket(COLOR_PRIOR, value, "int"));
}

int DaqcClient::legacyCwdGain()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(CWD_GAIN);
    });
    return result.toInt();
}

void DaqcClient::legacySetCwdGain(int value)
{
    createUpdateRequest(new RequestUpdatePacket(CWD_GAIN, value, "int"));
}

int DaqcClient::legacyDBaseLine()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(CWD_GAIN);
    });
    return result.toInt();
}

void DaqcClient::legacySetDBaseLine(int value)
{
    createUpdateRequest(new RequestUpdatePacket(D_BASELINE, value, "int"));
}

int DaqcClient::legacyDDynamic()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(D_DYNAMIC);
    });
    return result.toInt();
}

void DaqcClient::legacySetDDynamic(int value)
{
    createUpdateRequest(new RequestUpdatePacket(D_DYNAMIC, value, "int"));
}

int DaqcClient::legacyDNoiseRej()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(D_NOISE_REJECTION);
    });
    return result.toInt();
}

void DaqcClient::legacySetDNoiseRej(int value)
{
    createUpdateRequest(new RequestUpdatePacket(D_NOISE_REJECTION, value, "int"));
}

double DaqcClient::legacyDPRF()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(D_PRF);
    });
    return result.toDouble();
}

void DaqcClient::legacySetDPRF(double value)
{
    createUpdateRequest(new RequestUpdatePacket(D_PRF, value, "double"));
}

int DaqcClient::legacyDSoundVolum()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(D_SOUND_VOLUME);
    });
    return result.toInt();
}

void DaqcClient::legacySetDSoundVolum(int value)
{
    createUpdateRequest(new RequestUpdatePacket(D_SOUND_VOLUME, value, "int"));
}

int DaqcClient::legacyDSpeed()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(D_SPEED);
    });
    return result.toInt();
}

void DaqcClient::legacySetDSpeed(int value)
{
    createUpdateRequest(new RequestUpdatePacket(D_SPEED, value, "int"));
}

double DaqcClient::legacyDWallFilterFreq()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(D_SPEED);
    });
    return result.toDouble();
}

void DaqcClient::legacySetDWallFilterFreq(double value)
{
    createUpdateRequest(new RequestUpdatePacket(D_WALL_FILTER_FREQ, value, "double"));
}

int DaqcClient::legacyDepth()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DEPTH);
    });
    return result.toInt();
}

void DaqcClient::legacySetDepth(int value)
{
    createUpdateRequest(new RequestUpdatePacket(DEPTH, value, "int"));
}

int DaqcClient::legacyDirPwrGain()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DIR_PWR_GAIN);
    });
    return result.toInt();
}

void DaqcClient::legacySetDirPwrGain(int value)
{
    createUpdateRequest(new RequestUpdatePacket(DIR_PWR_GAIN, value, "int"));
}

int DaqcClient::legacyDscCapture()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DSC_CAPTURE);
    });
    return result.toInt();
}

void DaqcClient::legacySetDscCapture(int value)
{
    createUpdateRequest(new RequestUpdatePacket(DSC_CAPTURE, value, "int"));
}

int DaqcClient::legacyExamTypeID()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(EXAM_TYPE_ID);
    });
    return result.toInt();
}

void DaqcClient::legacySetExamTypeID(int value)
{
    createUpdateRequest(new RequestUpdatePacket(EXAM_TYPE_ID, value, "int"));
}

double DaqcClient::legacyFrameRelation()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(FRAME_RELATION);
    });
    return result.toDouble();
}

void DaqcClient::legacySetFrameRelation(double value)
{
    createUpdateRequest(new RequestUpdatePacket(FRAME_RELATION, value, "double"));
}

double DaqcClient::legacyFreq2()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(B_FREQUENCY_2);
    });
    return result.toDouble();
}

void DaqcClient::legacySetFreq2(double value)
{
    createUpdateRequest(new RequestUpdatePacket(B_FREQUENCY_2, value, "double"));
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
*/

double DaqcClient::legacyGetParameter(int id)
{
    auto result = createGetRequest([&id]{ 
        QVariantList values = { id };
        QStringList valueTypes = { "int" };
        return new RequestGetPacket(DaqcParameter::GET_PARAMETER, values, valueTypes); 
    });

    return result.toDouble();
}

int DaqcClient::legacyGetProbeInfo(int id)
{
    auto result = createGetRequest([&id]{ 
        QVariantList values = { id };
        QStringList valueTypes = { "int" };
        return new RequestGetPacket("test", values, valueTypes); 
    });

    return result.toInt();
}

void DaqcClient::legacyInit(int inum)
{
    QVariantList values = { inum };
    QStringList valueTypes = { "int" };
    createUpdateRequest(new RequestUpdatePacket(DaqcParameter::INIT, values, valueTypes));
}

void DaqcClient::legacyMoveROIColor(int x, int y)
{
    QVariantList values = { x, y };
    QStringList valueTypes = { "int", "int" };
    createUpdateRequest(new RequestUpdatePacket(DaqcParameter::MOVE_ROI_COLOR, values, valueTypes));
}

void DaqcClient::legacyRealtimeEn(int en)
{
    QVariantList values = { en };
    QStringList valueTypes = { "int" };
    createUpdateRequest(new RequestUpdatePacket(DaqcParameter::REALTIME_EN, values, valueTypes));
}

void DaqcClient::legacySetFlipH(int isFlip)
{
    QVariantList values = { isFlip };
    QStringList valueTypes = { "int" };
    createUpdateRequest(new RequestUpdatePacket(DaqcParameter::FLIP_H, values, valueTypes));
}

void DaqcClient::legacySetFlipV(int isFlip)
{
    QVariantList values = { isFlip };
    QStringList valueTypes = { "int" };
    createUpdateRequest(new RequestUpdatePacket(DaqcParameter::FLIP_V, values, valueTypes));
}

void DaqcClient::legacySetTGCPositions(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8)
{
    QVariantList values = { p1, p2, p3, p4, p5, p6, p7, p8 };
    QStringList valueTypes;
    for (int i = 0; i < 8; i++)
        valueTypes.push_back("int");
    createUpdateRequest(new RequestUpdatePacket(DaqcParameter::TGC_POSITIONS, values, valueTypes));
}

void DaqcClient::legacyZoomColorROI(int xDirection, int yDirection)
{
    QVariantList values = { xDirection, yDirection };
    QStringList valueTypes = { "int", "int" };
    createUpdateRequest(new RequestUpdatePacket(DaqcParameter::ZOOM_COLOR_ROI, values, valueTypes));
}

void DaqcClient::legacyFProbeType(int pbPort, int pbType)
{
    QVariantList values = { pbPort,  pbType };
    QStringList valueTypes = { "int", "int" };
    createUpdateRequest(new RequestUpdatePacket(DaqcParameter::F_PROBE_TYPE, values, valueTypes));
}

void DaqcClient::legacyStart()
{
    QVariantList values = {};
    QStringList valueTypes = {};
    createUpdateRequest(new RequestUpdatePacket(DaqcParameter::START, values, valueTypes));
}

void DaqcClient::legacyStop()
{
    QVariantList values = {};
    QStringList valueTypes = {};
    createUpdateRequest(new RequestUpdatePacket(DaqcParameter::STOP, values, valueTypes));
}

int DaqcClient::boolToIncrease(const bool &increase)
{
    return increase ? 1 : -1;
}

int DaqcClient::depthHardCode(const double & value)
{
    //no idea what these numbers are, they are from old code
    return value * 1.28 * 1000 / 130;
}

double DaqcClient::mmToCm(const double& value)
{
    return value / 10.;
}
