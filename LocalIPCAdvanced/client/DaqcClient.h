#pragma once

#include "Client.h"
#include <functional>
#include <QVariant>
#include <QImage>

class Client;
class QEventLoop;
class Packet;
class QTimer;

enum class BcdSynchro : int
{
    OFF = -1,
    SYNCHRO = 1,
    UPDATE = 2
};

class DaqcClient : public Client
{
    Q_OBJECT
public:
    DaqcClient(QObject* parent = nullptr);
    ~DaqcClient();
    void connectToServer() override;
    int testGetApi();
    void testSetApi(int value);
    // get functions

    // TO CHECK
    bool isConnected();

    double getRegionPhysicalDeltaX();
    double getRegionPhysicalDeltaY();
    int getBGain();
    int getCGain();
    double getXmlDepth();
    int getDepthMm();
    double getDepthCm();
    double getBFrequency();
    double getBFrequency2();
    // TO CHECK
    int getChroma();

    int getFavg();
    int getLavg();
    int getContrast();
    double getCPrf();
    double getDPrf();
    double getCWf();
    double getDWf();
    int getSensitivity();
    int getSwingAngle();//same value for c and d mode
    double getSv();
    double getCa();
    int getDSpeed();
    int getNoiseReject();
    int getAudio();
    // TO CHECK
    int getRotation();

    double getSpacingX();
    double getSpacingY();
    // TO CHECK
    bool isBb();
    bool isUp();

    bool isThi();
    // TO CHECK
    bool isCenterLine();
    bool isRoiSite();
    bool isRoiSize();

    bool isCInvert();
    bool isDInvert();
    bool isCAutoTrace();
    // TO CHECK
    bool isDAutoTrace();

    bool isUpdate();
    bool isSynchro();
    // TO CHECK
    QPoint getRoiPosition();
    int getDualConvexOrLinearChannel();
    bool isDualModeOn();
    // increase/decrease functions
    void setBGain(bool increase);
    void setCGain(bool increase);
    void setDepth(bool increase);
    void setBFrequency(bool increase);
    void setBFrequency2(bool increase);

    // TO CHECK
    void setChroma(bool increase);

    void setFavg(bool increase);
    void setLavg(bool increase);

    // TO CHECK
    void setContrast(bool increase);


    void setCPrf(bool increase);
    void setDPrf(bool increase);
    void setCWf(bool increase);
    void setDWf(bool increase);
    void setSensitivity(bool increase);
    void setSwingAngle(bool increase);
    void setSv(bool increase);
    void setCa(bool increase);
    void setDSpeed(bool increase);
    void setNoiseReject(bool increase);
    void setAudio(bool increase);

    // TO CHECK
    void setBaseline(bool increase);
    void setRotation(bool increase);


    // set functions
    void setBb(bool value);
    void setUp(bool value);
    void setThi(bool value);
    void setCenterLine(bool value);
    void setRoiSite(bool value);
    void setRoiSize(bool value);
    void setCInvert(bool value);
    void setDInvert(bool value);
    void setCAutoTrace(bool value);
    void setDAutoTrace(bool value);
    void setUpdate(bool value);//affects setSynchro
    void setSynchro(bool value);//affects setUpdate
    void setDualMode(bool value);
    void setImgProcValue(int index, const std::vector<int>& params);
    //other functions

    // TO CHECK
    void cancelRoi();

    //


    //all functions from daqclib.h are prepended with "legacy"
    void legacySetACUI(int value);
    int legacyACUI();
    void legacyFacuiParams(int index, int value);
    int legacyBCDSynChro();
    void legacySetBCDSynChro(int value);
    int legacyBDynamic();
    void legacySetBDynamic(int value);
    int legacyCBaseLine();
    double legacyCPRF();
    bool legacyColorInvert();
    void legacySetColorInvert(bool value);
    int legacyDBaseLine();
    int legacyDDynamic();
    void legacySetDDynamic(int value);
    double legacyDPRF();
    void legacySetExamTypeID(int value);
    void legacySetImageProcess(int value);
    int legacyPersistenceColor();
    void legacySetPersistenceColor(int value);
    void legacySetProbePOS(int value);
    int legacyProbeSEL();
    void legacySetRadium(double value);
    int legacyTHI();
    void legacySetTHI(int value);
    int legacyCAutoTrace();
    void legacySetESpin(double value);
    void legacySetPwifBuffms(int value);
    int legacyScanMode();
    void legacySetScanMode(int value);
    double legacyGetParameter(int id);
    // This function is not real-time. This result will be changed only when the ultrasound machine start
    int legacyGetProbeInfo(int id);
    void legacyInit(int inum);
    void legacyMoveROIColor(int x, int y);
    void legacyPalette(int colorID, int bright, int ts);
    void legacyRealtimeEn(int en);
    void legacySetFlipH(int isFlip);
    void legacySetFlipV(int isFlip);
    void legacySetTGCPositions(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8);
    void legacyZoomColorROI(int xDirection, int yDirection);
    // F means forward
    void legacyFProbeType(int pbPort, int pbType);
    void legacyStart();
    void legacyStop();
private slots:
    void requestGetParameters();
private:
    int boolToIncrease(const bool& increase);
    int depthHardCode(const double &value);
    double mmToCm(const double &value);

    void requestTest();


    QTimer* m_requestParameterTimer;
};