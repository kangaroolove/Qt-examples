#include "DaqcClient.h"
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
    m_chroma(0),
    m_rotation(0),
    m_bb(false),
    m_isUp(false),
    m_centerLine(false),
    m_roi(RoiState::OFF),
    m_dAutoTrace(false),
    m_imgProcIndex(1)
{
}

DaqcClient::~DaqcClient()
{
}

void DaqcClient::connectToServer()
{
    m_worker->connectToServer("cms/daqc");
    if (m_worker->waitForConnected())
        qDebug()<<"Connect to server";
    else 
        qDebug()<<"Cannot connect to server";
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

bool DaqcClient::isConnected() const
{
    return m_connected;
}

double DaqcClient::getRegionPhysicalDeltaX() const
{
    return getResult(DaqcParameter::REGION_PHYSICAL_DELTA_X).toDouble();
}

double DaqcClient::getRegionPhysicalDeltaY() const
{
    return getResult(DaqcParameter::REGION_PHYSICAL_DELTA_Y).toDouble();
}

int DaqcClient::getBGain() const
{
    return getResult(DaqcParameter::B_GAIN).toInt();
}

int DaqcClient::getCGain() const
{
    return getResult(DaqcParameter::C_GAIN).toInt();
}

double DaqcClient::getXmlDepth() const
{
    return getResult(DaqcParameter::XML_DEPTH).toDouble();
}

int DaqcClient::getDepthMm()
{
    return depthHardCode(getXmlDepth());
}

double DaqcClient::getDepthCm()
{
    return mmToCm(getDepthMm());
}

double DaqcClient::getBFrequency() const
{
    return getResult(DaqcParameter::B_FREQUENCY).toDouble();
}

double DaqcClient::getBFrequency2() const
{
    return getResult(DaqcParameter::B_FREQUENCY_2).toDouble();
}

int DaqcClient::getChroma() const
{
    return m_chroma;
}

int DaqcClient::getFavg() const
{
    // original interface return double
    return getResult(DaqcParameter::FAVG).toInt();
}

int DaqcClient::getLavg() const
{
    return getResult(DaqcParameter::LAVG).toInt();
}

int DaqcClient::getContrast()
{
    return legacyBDynamic();
}

double DaqcClient::getCPrf()
{
    return legacyCPRF();
}

double DaqcClient::getDPrf() const
{
    return getResult(DaqcParameter::D_PRF).toDouble();
}

double DaqcClient::getCWf() const
{
    return getResult(DaqcParameter::C_WF).toDouble();
}

double DaqcClient::getDWf() const
{
    return getResult(DaqcParameter::D_WF).toDouble();
}

int DaqcClient::getSensitivity() const
{
    return getResult(DaqcParameter::SENSITIVITY).toInt();
}

int DaqcClient::getSwingAngle() const
{
    return getResult(DaqcParameter::SWING_ANGLE).toInt();
}

double DaqcClient::getSv() const
{
    return getResult(DaqcParameter::SV).toDouble();
}

double DaqcClient::getCa() const
{
    return getResult(DaqcParameter::CA).toDouble();
}

int DaqcClient::getDSpeed() const
{
    return getResult(DaqcParameter::D_SPEED).toInt();
}

int DaqcClient::getNoiseReject() const
{
    return getResult(DaqcParameter::D_NOISE_REJECT).toInt();
}

int DaqcClient::getAudio() const
{
    return getResult(DaqcParameter::D_SOUND_VOLUME).toInt();
}

int DaqcClient::getRotation() const
{
    return 0;
}

double DaqcClient::getSpacingX() const
{
    return getResult(DaqcParameter::SPACING_X).toDouble();
}

double DaqcClient::getSpacingY() const
{
    return getResult(DaqcParameter::SPACING_Y).toDouble();
}

bool DaqcClient::isBb() const
{
    return m_bb;
}

bool DaqcClient::isUp() const
{
    return m_isUp;
}

bool DaqcClient::isThi()
{
    return legacyTHI() == 1;
}

bool DaqcClient::isCenterLine() const
{
    return m_centerLine;
}

bool DaqcClient::isRoiSite() const
{
    return m_roi == RoiState::SITE;
}

bool DaqcClient::isRoiSize() const
{
    return m_roi == RoiState::SIZE;
}

bool DaqcClient::isCInvert()
{
    return legacyColorInvert();
}

bool DaqcClient::isDInvert() const
{
    return getResult(DaqcParameter::D_INVERT).toBool();
}

bool DaqcClient::isCAutoTrace()
{
    return legacyCAutoTrace() == 1;
}

bool DaqcClient::isDAutoTrace() const
{
    return m_dAutoTrace;
}

bool DaqcClient::isUpdate()
{
    return legacyBCDSynChro() == (int)BcdSynchro::UPDATE;
}

bool DaqcClient::isSynchro()
{
    return legacyBCDSynChro() == (int)BcdSynchro::SYNCHRO;
}

QPoint DaqcClient::getRoiPosition() const
{
    return QPoint(getResult(DaqcParameter::ROI_POSITION_X).toInt(), getResult(DaqcParameter::ROI_POSITION_Y).toInt());
}

int DaqcClient::getImageCurrentChannel() const
{
    return getResult(DaqcParameter::IMAGE_CURRENT_CHANNEL).toInt();
}

bool DaqcClient::isDualModeOn() const
{
    return getResult(DaqcParameter::DUAL_MODE).toBool();
}

double DaqcClient::getFps() const
{
    return getResult(DaqcParameter::FPS).toDouble();
}

int DaqcClient::getImgProcIndex() const
{
    return m_imgProcIndex;
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
    static const int MAX = 10;
    m_chroma = (m_chroma + (increase ? 1 : MAX)) % (MAX + 1);
    legacyPalette(m_chroma, 0, 0);
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
    static const int MAX = 75;
    static const int MIN = 30;
    static const int STEP = 5;
    int contrast = getContrast();
    contrast += (increase ? STEP : -STEP);
    if (contrast > MAX)
        contrast = MIN;
    else if (contrast < MIN)
        contrast = MAX;

    QVariantList values = { contrast };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::CONTRAST, values, valueTypes));
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

void DaqcClient::setDBaseline(bool increase)
{
    QVariantList values = { boolToIncrease(increase) };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::D_BASELINE, values, valueTypes));
}

void DaqcClient::setRotation(bool increase)
{
    static const int MAX = 270;
    static const int MIN = 0;
    static const int STEP = 90;
    int value = m_rotation;
    value += (increase ? STEP : -STEP);
    if (value > MAX)
        value = MIN;
    else if (value < MIN)
        value = MAX;
    m_rotation = value;
    emit rotationUpdated(m_rotation);
}

void DaqcClient::setBb(bool value)
{
    m_bb = value;
    emit bbUpdated(value);

    QVariantList values = { };
    QStringList valueTypes = { };
    if (m_bb)
        createRequest(new RequestUpdatePacket(DaqcParameter::MODE_2B, values, valueTypes));
    else 
    {
        values.push_back(legacyScanMode());
        valueTypes.push_back("int");
        createRequest(new RequestUpdatePacket(DaqcParameter::SCAN_MODE, values, valueTypes));
    }
}

void DaqcClient::setUp(bool value)
{
    if (m_isUp == value)
        return;
    m_isUp = value;
    emit upUpdated(value);
}

void DaqcClient::setThi(bool value)
{
    bool thi = isThi();
    if (thi == value)
        return;

    bool on = isDualModeOn();
    legacySetTHI(boolToIncrease(value));
    if (value && on)
        legacyRealtimeEn(on);
}

void DaqcClient::setCenterLine(bool value)
{
    if (m_centerLine == value)
        return;
    m_centerLine = value;
    emit centerLineUpdated(value);
}

void DaqcClient::setRoiSite(bool value)
{
    if (!value)
        return cancelRoi();
    m_roi = RoiState::SITE;
    emit roiSiteOn();
}

void DaqcClient::setRoiSize(bool value)
{
    if (!value)
        return cancelRoi();
    m_roi = RoiState::SIZE;
    emit roiSizeOn();
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
    if (m_dAutoTrace == value)
        return;

    m_dAutoTrace = value;
    //toggles instead of only setting on
    QVariantList values = { true };
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
    m_imgProcIndex = index;
}

void DaqcClient::cancelRoi()
{
    m_roi = RoiState::OFF;
    emit roiCancelled();
}

void DaqcClient::legacySetACUI(int value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::ACUI, values, valueTypes));
}

int DaqcClient::legacyACUI()
{
    return getResult(DaqcParameter::ACUI).toInt();
}

void DaqcClient::legacyFacuiParams(int index, int value)
{
    QVariantList values = { index, value};
    QStringList valueTypes = { "int", "int"};
    createRequest(new RequestUpdatePacket(DaqcParameter::ACUI_PARAMETER, values, valueTypes));
}

int DaqcClient::legacyBCDSynChro()
{
    return getResult(DaqcParameter::B_C_D_SYNCHRO).toInt();
}

void DaqcClient::legacySetBCDSynChro(int value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::B_C_D_SYNCHRO, values, valueTypes));
}

int DaqcClient::legacyBDynamic()
{
    return getResult(DaqcParameter::B_DYNAMIC).toInt();
}

void DaqcClient::legacySetBDynamic(int value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::B_DYNAMIC, values, valueTypes));
}

int DaqcClient::legacyCBaseLine()
{
    return getResult(DaqcParameter::C_BASE_LINE).toInt();
}

double DaqcClient::legacyCPRF()
{
    return getResult(DaqcParameter::C_PRF).toDouble();
}

bool DaqcClient::legacyColorInvert()
{
    return getResult(DaqcParameter::COLOR_INVERT).toBool();
}

void DaqcClient::legacySetColorInvert(bool value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "bool" };
    createRequest(new RequestUpdatePacket(DaqcParameter::COLOR_INVERT, values, valueTypes));
}

int DaqcClient::legacyDBaseLine()
{
    return getResult(DaqcParameter::D_BASELINE).toInt();
}

int DaqcClient::legacyDDynamic()
{
    return getResult(DaqcParameter::D_DYNAMIC).toInt();
}

void DaqcClient::legacySetDDynamic(int value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::D_DYNAMIC, values, valueTypes));
}

double DaqcClient::legacyDPRF()
{
    return getResult(DaqcParameter::D_PRF).toDouble();
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
    return getResult(DaqcParameter::PERSISTENCE_COLOR).toInt();
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
    return getResult(DaqcParameter::PROBE_SEL).toInt();
}

void DaqcClient::legacySetRadium(double value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "double" };
    createRequest(new RequestUpdatePacket(DaqcParameter::RADIUM, values, valueTypes));
}

int DaqcClient::legacyTHI()
{
    return getResult(DaqcParameter::THI).toInt();
}

void DaqcClient::legacySetTHI(int value)
{
    QVariantList values = { value };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::THI, values, valueTypes));
}

int DaqcClient::legacyCAutoTrace()
{
    return getResult(DaqcParameter::C_AUTO_TRACE).toInt();
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
    return getResult(DaqcParameter::SCAN_MODE).toInt();
}

void DaqcClient::legacySetScanMode(int value)
{
    if (m_bb)
        m_bb = false;

    QVariantList values = { value };
    QStringList valueTypes = { "int" };
    createRequest(new RequestUpdatePacket(DaqcParameter::SCAN_MODE, values, valueTypes));
}

double DaqcClient::legacyGetParameter(int id)
{
    return getResult(DaqcParameter::GET_PARAMETER + QString::number(id)).toDouble();
}

int DaqcClient::legacyGetProbeInfo(int port)
{
    return getResult(DaqcParameter::PROBE_INFO + QString::number(port)).toInt();
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
