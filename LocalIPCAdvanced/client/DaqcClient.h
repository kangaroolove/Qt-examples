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

enum class RoiState : unsigned int;
class UpdateInfoWorker;

class DaqcClient : public Client
{
    Q_OBJECT
public:
    DaqcClient(QObject* parent = nullptr);
    ~DaqcClient();
    void connectToServer() override;
    int testGetApi();
    void testSetApi(int value);
    bool isConnected() const;
    // get functions
    double getRegionPhysicalDeltaX() const;
    double getRegionPhysicalDeltaY() const;
    int getBGain() const;
    int getCGain() const;
    double getXmlDepth() const;
    int getDepthMm();
    double getDepthCm();
    double getBFrequency() const;
    double getBFrequency2() const;
    int getChroma() const;
    int getFavg() const;
    int getLavg() const;
    int getContrast();
    double getCPrf();
    double getDPrf() const;
    double getCWf() const;
    double getDWf() const;
    int getSensitivity() const;
    // same value for c and d mode
    int getSwingAngle() const;
    double getSv() const;
    double getCa() const;
    int getDSpeed() const;
    int getNoiseReject() const;
    int getAudio() const;
    int getRotation() const;
    double getSpacingX() const;
    double getSpacingY() const;
    bool isBb() const;
    bool isUp() const;
    bool isThi();
    bool isCenterLine() const;
    bool isRoiSite() const;
    bool isRoiSize() const;
    bool isCInvert();
    bool isDInvert() const;
    bool isCAutoTrace();
    bool isDAutoTrace() const;
    bool isUpdate();
    bool isSynchro();
    QPoint getRoiPosition() const;
    int getImageCurrentChannel() const;
    bool isDualModeOn() const;
    // increase/decrease functions
    void setBGain(bool increase);
    void setCGain(bool increase);
    void setDepth(bool increase);
    void setBFrequency(bool increase);
    void setBFrequency2(bool increase);
    void setChroma(bool increase);
    void setFavg(bool increase);
    void setLavg(bool increase);
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
    void setDBaseline(bool increase);
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
    // affects setSynchro
    void setUpdate(bool value);
    // affects setUpdate
    void setSynchro(bool value);
    void setDualMode(bool value);
    void setImgProcValue(int index, const std::vector<int>& params);
    //other functions
    void cancelRoi();

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
    int legacyGetProbeInfo(int port);
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
signals:
    void rotationUpdated(int rotation);
    void bbUpdated(bool isBb);
    void upUpdated(bool isUp);
    void centerLineUpdated(bool isCenterLine);
    // roi signal split into 3 to avoid casting enum to int param, could change back if better
    void roiSiteOn();
    void roiSizeOn();
    void roiCancelled();
private:
    int boolToIncrease(const bool& increase);
    int depthHardCode(const double &value);
    double mmToCm(const double &value);

    int m_chroma;
    int m_rotation;
    bool m_bb;
    bool m_isUp;
    bool m_centerLine;
    RoiState m_roi;
    bool m_dAutoTrace;
};