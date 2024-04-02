#include "DaqcClient.h"
#include "RequestGetPacket.h"
#include "RequestUpdatePacket.h"
#include "Client.h"
#include "DaqcClientDef.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QThreadPool>
#include <QEventLoop>
#include <QImage>
#include <QTimer>

DaqcClient::DaqcClient(QObject* parent) :
    Client(parent),
    m_requestParameterTimer(new QTimer(this))
{
    m_requestParameterTimer->setInterval(400);

    connect(m_requestParameterTimer, &QTimer::timeout, this, &DaqcClient::requestGetParameters);
    connect(this, &DaqcClient::connected, this, [this]{
        m_requestParameterTimer->start();
    });
}

DaqcClient::~DaqcClient()
{
}

void DaqcClient::connectToServer()
{
    qDebug()<<"Connect to server";
    m_worker->connectToServer("Daqc");
}

int DaqcClient::testGetApi()
{
    return getResult(DaqcParameter::TEST).toInt();
}

void DaqcClient::testSetApi(int value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::TEST, values, valueTypes));
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
        return new RequestGetPacket(DaqcParameter::D_NOISE_REJECT);
    });
    return result.toInt();
}

int DaqcClient::getAudio()
{
    auto result = createGetRequest([]{
        return new RequestGetPacket(DaqcParameter::D_SOUND_VOLUME);
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
    createRequest(new RequestUpdatePacket(DaqcParameter::B_GAIN, values, valueTypes));
}

void DaqcClient::setCGain(bool increase)
{
    QVariantList values = { boolToIncrease(increase) };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::C_GAIN, values, valueTypes));
}

void DaqcClient::setDepth(bool increase)
{
    QVariantList values = { boolToIncrease(increase) };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::DEPTH, values, valueTypes));
}

void DaqcClient::setBFrequency(bool increase)
{
    QVariantList values = { boolToIncrease(increase) };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::B_FREQUENCY, values, valueTypes));
}

void DaqcClient::setBFrequency2(bool increase)
{
    QVariantList values = { boolToIncrease(increase) };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::B_FREQUENCY_2, values, valueTypes));
}

void DaqcClient::setChroma(bool increase)
{
    QVariantList values = { boolToIncrease(increase) };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::CHROMA, values, valueTypes));
}

void DaqcClient::setFavg(bool increase)
{
    QVariantList values = { boolToIncrease(increase) };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::FAVG, values, valueTypes));
}

void DaqcClient::setLavg(bool increase)
{
    QVariantList values = { boolToIncrease(increase) };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::LAVG, values, valueTypes));
}

void DaqcClient::setContrast(bool increase)
{
    // QVariantList values = { boolToIncrease(increase) };
    // QStringList valueTypes = { "int" };
    // createUpdateRequest(new RequestUpdatePacket(DaqcParameter::CONTRAST, values, valueTypes));
}

void DaqcClient::setCPrf(bool increase)
{
    QVariantList values = { boolToIncrease(increase) };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::C_PRF, values, valueTypes));
}

void DaqcClient::setDPrf(bool increase)
{
    QVariantList values = { boolToIncrease(increase) };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::D_PRF, values, valueTypes));
}

void DaqcClient::setCWf(bool increase)
{
    QVariantList values = { boolToIncrease(increase) };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::C_WF, values, valueTypes));
}

void DaqcClient::setDWf(bool increase)
{
    QVariantList values = { boolToIncrease(increase) };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::D_WF, values, valueTypes));
}

void DaqcClient::setSensitivity(bool increase)
{
    QVariantList values = { boolToIncrease(increase) };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::SENSITIVITY, values, valueTypes));
}

void DaqcClient::setSwingAngle(bool increase)
{
    QVariantList values = { boolToIncrease(increase) };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::SWING_ANGLE, values, valueTypes));
}

void DaqcClient::setSv(bool increase)
{
    QVariantList values = { boolToIncrease(increase) };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::SV, values, valueTypes));
}

void DaqcClient::setCa(bool increase)
{
    QVariantList values = { boolToIncrease(increase) };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::CA, values, valueTypes));
}

void DaqcClient::setDSpeed(bool increase)
{
    QVariantList values = { boolToIncrease(increase) };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::D_SPEED, values, valueTypes));
}

void DaqcClient::setNoiseReject(bool increase)
{
    QVariantList values = { boolToIncrease(increase) };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::D_NOISE_REJECT, values, valueTypes));
}

void DaqcClient::setAudio(bool increase)
{
    QVariantList values = { boolToIncrease(increase) };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::D_SOUND_VOLUME, values, valueTypes));
}

void DaqcClient::setBaseline(bool increase)
{
    //createUpdateRequest(new RequestUpdatePacket(DaqcParameter::BASELINE, boolToIncrease(increase), "int"));
}

void DaqcClient::setRotation(bool increase)
{

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
}

void DaqcClient::setRoiSize(bool value)
{
    //createUpdateRequest(new RequestUpdatePacket(ROI_SIZE, value, "bool"));
}

void DaqcClient::setCInvert(bool value)
{
    legacySetColorInvert(value);
}

void DaqcClient::setDInvert(bool value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "bool" };
    createRequest(new RequestUpdatePacket(DaqcParameter::D_INVERT, values, valueTypes));
}

void DaqcClient::setCAutoTrace(bool value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "bool" };
    createRequest(new RequestUpdatePacket(DaqcParameter::C_AUTO_TRACE, values, valueTypes));
}

void DaqcClient::setDAutoTrace(bool value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "bool" };
    createRequest(new RequestUpdatePacket(DaqcParameter::D_AUTO_TRACE, values, valueTypes));
}

void DaqcClient::setUpdate(bool value)
{
    int parameter = value ? (int)BcdSynchro::UPDATE : (int)BcdSynchro::OFF;
    legacySetBCDSynChro(parameter);
}

void DaqcClient::setSynchro(bool value)
{
    int parameter = value ? (int)BcdSynchro::SYNCHRO : (int)BcdSynchro::OFF;
    legacySetBCDSynChro(parameter);
}

void DaqcClient::setDualMode(bool value)
{
    legacyRealtimeEn(value);
}

void DaqcClient::setImgProcValue(int index, const std::vector<int> &params)
{
    if (params.size() < 27)
        return;
    
    for (int i = 0; i < 27; i++)
        legacyFacuiParams(i + 3, params.at(i));
    legacySetACUI(index);
}

void DaqcClient::cancelRoi()
{
}

void DaqcClient::legacySetACUI(int value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::ACUI, values, valueTypes));
}

int DaqcClient::legacyACUI()
{
    auto result = createGetRequest([]{ 
        return new RequestGetPacket(DaqcParameter::ACUI); 
    });

    return result.toInt();
}

void DaqcClient::legacyFacuiParams(int index, int value)
{
    QVariantList values = { index, value};
    QStringList valueTypes = { "int", "int"};
    createRequest(new RequestUpdatePacket(DaqcParameter::ACUI_PARAMETER, values, valueTypes));
}

int DaqcClient::legacyBCDSynChro()
{
    auto result = createGetRequest([]{ 
        return new RequestGetPacket(DaqcParameter::B_C_D_SYNCHRO); 
    });

    return result.toInt();
}

void DaqcClient::legacySetBCDSynChro(int value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::B_C_D_SYNCHRO, values, valueTypes));
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
    createRequest(new RequestUpdatePacket(DaqcParameter::B_DYNAMIC, values, valueTypes));
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

void DaqcClient::legacySetColorInvert(bool value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "bool" };
    createRequest(new RequestUpdatePacket(DaqcParameter::COLOR_INVERT, values, valueTypes));
}

int DaqcClient::legacyDBaseLine()
{
    auto result = createGetRequest([]{ 
        return new RequestGetPacket(DaqcParameter::D_BASELINE); 
    });

    return result.toInt();
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
    createRequest(new RequestUpdatePacket(DaqcParameter::D_DYNAMIC, values, valueTypes));
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
    createRequest(new RequestUpdatePacket(DaqcParameter::EXAM_TYPE_ID, values, valueTypes));
}

void DaqcClient::legacySetImageProcess(int value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::IMAGE_PROCESS, values, valueTypes));
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
    createRequest(new RequestUpdatePacket(DaqcParameter::PERSISTENCE_COLOR, values, valueTypes));
}

void DaqcClient::legacySetProbePOS(int value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::PROBE_POS, values, valueTypes));
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
    createRequest(new RequestUpdatePacket(DaqcParameter::RADIUM, values, valueTypes));
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
    createRequest(new RequestUpdatePacket(DaqcParameter::ESPIN, values, valueTypes));
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
    createRequest(new RequestUpdatePacket(DaqcParameter::ESPIN, values, valueTypes));
}

void DaqcClient::legacySetPwifBuffms(int value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::PWIF_BUFF_MS, values, valueTypes));
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
    createRequest(new RequestUpdatePacket(DaqcParameter::SCAN_MODE, values, valueTypes));
}

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
        return new RequestGetPacket(DaqcParameter::PROBE_INFO, values, valueTypes); 
    });

    return result.toInt();
}

void DaqcClient::legacyInit(int inum)
{
    QVariantList values = { inum };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::INIT, values, valueTypes));
}

void DaqcClient::legacyMoveROIColor(int x, int y)
{
    QVariantList values = { x, y };
    QStringList valueTypes = { "int", "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::MOVE_ROI_COLOR, values, valueTypes));
}

void DaqcClient::legacyPalette(int colorID, int bright, int ts)
{
    QVariantList values = { colorID, bright, ts };
    QStringList valueTypes = { "int", "int", "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::PALETTE, values, valueTypes));
}

void DaqcClient::legacyRealtimeEn(int en)
{
    QVariantList values = { en };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::REALTIME_EN, values, valueTypes));
}

void DaqcClient::legacySetFlipH(int isFlip)
{
    QVariantList values = { isFlip };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::FLIP_H, values, valueTypes));
}

void DaqcClient::legacySetFlipV(int isFlip)
{
    QVariantList values = { isFlip };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::FLIP_V, values, valueTypes));
}

void DaqcClient::legacySetTGCPositions(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8)
{
    QVariantList values = { p1, p2, p3, p4, p5, p6, p7, p8 };
    QStringList valueTypes;
    for (int i = 0; i < 8; i++)
        valueTypes.push_back("int");
    createRequest(new RequestUpdatePacket(DaqcParameter::TGC_POSITIONS, values, valueTypes));
}

void DaqcClient::legacyZoomColorROI(int xDirection, int yDirection)
{
    QVariantList values = { xDirection, yDirection };
    QStringList valueTypes = { "int", "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::ZOOM_COLOR_ROI, values, valueTypes));
}

void DaqcClient::legacyFProbeType(int pbPort, int pbType)
{
    QVariantList values = { pbPort,  pbType };
    QStringList valueTypes = { "int", "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::F_PROBE_TYPE, values, valueTypes));
}

void DaqcClient::legacyStart()
{
    QVariantList values = {};
    QStringList valueTypes = {};
    createRequest(new RequestUpdatePacket(DaqcParameter::START, values, valueTypes));
}

void DaqcClient::legacyStop()
{
    QVariantList values = {};
    QStringList valueTypes = {};
    createRequest(new RequestUpdatePacket(DaqcParameter::STOP, values, valueTypes));
}

void DaqcClient::requestGetParameters()
{
    requestTest();
    static int i = 0;
    if (i < 10)
    {
        ++i;
    }
    else 
        i = 0;

    testSetApi(i);
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

void DaqcClient::requestTest()
{
    QVariantList values = { 50 };
    QStringList valueTypes = { "int" };
    createRequest(new RequestGetPacket(DaqcParameter::TEST, values, valueTypes));
}
