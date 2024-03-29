#pragma once

#include "Client.h"
#include <functional>
#include <QVariant>
#include <QImage>

class Client;
class QEventLoop;
class Packet;

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
    void start() override;
    int testGetApi();
    void testSetApi(bool isTest);
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
    int getImgProc();

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
    void setMGain(bool increase);
    void setDepth(bool increase);
    void setBFrequency(bool increase);
    void setBFrequency2(bool increase);
    void setMFrequency(bool increase);
    void setChroma(bool increase);
    void setImgProc(bool increase, const std::vector<int>& params);
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
    void setMSpeed(bool increase);
    void setNoiseReject(bool increase);
    void setAudio(bool increase);
    void setBaseline(bool increase);
    void setRotation(bool increase);
    // set functions
    void setBGainValue(int value);
    void setDepthValue(int value);
    void setBFrequencyValue(double value);
    void setChromaValue(int value);
    void setImgProcValue(int value, const std::vector<int>& params);
    void setFavgValue(int value);
    void setLavgValue(int value);
    void setContrastValue(int value);
    void setRotationValue(int value);
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
    //other functions
    void cancelRoi();

    //all functions from daqclib.h are prepended with "legacy"
    // int legacyACUI();
    void legacySetACUI(int value);
    // int legacyAPower();
    // void legacySetAPower(int value);
    // int legacyAnatomyLine();
    // void legacySetAnatomyLine(int value);
    int legacyBCDSynChro();
    // void legacySetBCDSynChro(int value);
    int legacyBDynamic();
    void legacySetBDynamic(int value);
    // int legacyBGain();
    // void legacySetBGain(int value);
    // int legacyBGain2();
    // void legacySetBGain2(int value);
    // int legacyBNoiseRej();
    // void legacySetBNoiseRej(int value);
    int legacyCBaseLine();
    // void legacySetCBaseLine(int value);
    // int legacyCDynamic();
    // void legacySetCDynamic(int value);
    // double legacyCFreq();
    // void legacySetCFreq(double value);
    // int legacyCGain();
    // void legacySetCGain(int value);
    // int legacyCNoiseRej();
    // void legacySetCNoiseRej(int value);
    double legacyCPRF();
    // void legacySetCPRF(double value);
    // double legacyCWallFilterFreq();
    // void legacySetCWallFilterFreq(double value);
    bool legacyColorInvert();
    // void legacySetColorInvert(bool value);
    // int legacyColorPrior();
    // void legacySetColorPrior(int value);
    // int legacyCwdGain();
    // void legacySetCwdGain(int value);
    // int legacyDBaseLine();
    // void legacySetDBaseLine(int value);
    int legacyDDynamic();
    void legacySetDDynamic(int value);
    // int legacyDNoiseRej();
    // void legacySetDNoiseRej(int value);
    double legacyDPRF();
    // void legacySetDPRF(double value);
    // int legacyDSoundVolum();
    // void legacySetDSoundVolum(int value);
    // int legacyDSpeed();
    // void legacySetDSpeed(int value);
    // double legacyDWallFilterFreq();
    // void legacySetDWallFilterFreq(double value);
    // int legacyDepth();
    // void legacySetDepth(int value);
    // int legacyDirPwrGain();
    // void legacySetDirPwrGain(int value);
    // int legacyDscCapture();
    // void legacySetDscCapture(int value);
    // int legacyExamTypeID();
    void legacySetExamTypeID(int value);
    // double legacyFrameRelation();
    // void legacySetFrameRelation(double value);
    // double legacyFreq2();
    // void legacySetFreq2(double value);
    // double legacyFrequence();
    // void legacySetFrequence(double value);
    // int legacyGetDscStop();
    // void legacySetGetDscStop(int value);
    // int legacyImageProcess();
    void legacySetImageProcess(int value);
    // int legacyLavgRelation();
    // void legacySetLavgRelation(int value);
    // int legacyLineDensity();
    // void legacySetLineDensity(int value);
    // int legacyMGain();
    // void legacySetMGain(int value);
    // double legacyMSpeed();
    // void legacySetMSpeed(double value);
    // int legacyPWDCompress();
    // void legacySetPWDCompress(int value);
    // double legacyPWDCorrectionAngle();
    // void legacySetPWDCorrectionAngle(double value);
    // double legacyPWDgateSize();
    // void legacySetPWDgateSize(double value);
    // double legacyPWDsampleDepth();
    // void legacySetPWDsampleDepth(double value);
    // int legacyPWDstartPos();
    // void legacySetPWDstartPos(int value);
    int legacyPersistenceColor();
    void legacySetPersistenceColor(int value);
    // int legacyProbePOS();
    void legacySetProbePOS(int value);
    int legacyProbeSEL();
    // void legacySetProbeSEL(int value);
    // int legacyPwdGain();
    // void legacySetPwdGain(int value);
    // bool legacyPwdInvert();
    // void legacySetPwdInvert(bool value);
    // int legacyPwrGain();
    // void legacySetPwrGain(int value);
    // int legacyPwrMode();
    // void legacySetPwrMode(int value);
    // int legacyROISwingAngle();
    // void legacySetROISwingAngle(int value);
    // double legacyRadium();
    void legacySetRadium(double value);
    // int legacyResetProbe();
    // void legacySetResetProbe(int value);
    // int legacyScanLine();
    // void legacySetScanLine(int value);
    int legacyTHI();
    void legacySetTHI(int value);
    // int legacyZoomImg();
    // void legacySetZoomImg(int value);
    // int legacyBFocusLch();
    // void legacySetBFocusLch(int value);
    int legacyCAutoTrace();
    // void legacySetCAutoTrace(int value);
    // int legacyCFocusLch();
    // void legacySetCFocusLch(int value);
    // double legacyESpin();
    void legacySetESpin(double value);
    // int legacyImgExtend();
    // void legacySetImgExtend(int value);
    // int legacyPosNeg();
    // void legacySetPosNeg(int value);
    // int legacyPwifBuffms();
    void legacySetPwifBuffms(int value);
    // int legacyScanFeature();
    // void legacySetScanFeature(int value);
    int legacyScanMode();
    void legacySetScanMode(int value);
    // int legacySmooth();
    // void legacySetSmooth(int value);
    // void legacyAboutBox();
    // void legacyFacuiParams(int pXh, int vAcui);
    // void legacyGetColorDopplerROI(int startPos, int endPos, int startDepth, int endDepth);
    // int legacyGetDepthSf();
    // double legacyGetFPS();
    double legacyGetParameter(int id);
    // // This function is not real-time. This result will be changed only when the ultrasound machine start
    int legacyGetProbeInfo(int id);
    // void legacyGetTGCPositions(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8);
    void legacyInit(int inum);
    // void legacyMode2B();
    // void legacyMode4B(int wid);
    // void legacyMoveColorROI(int LeftRight, int UpDown);
    void legacyMoveROIColor(int x, int y);
    // void legacyPalette(int colorID, int bright, int ts);
    void legacyRealtimeEn(int en);
    // void legacySetColorDopplerROI(int startPos, int endPos, int startDepth, int endDepth);
    void legacySetFlipH(int isFlip);
    void legacySetFlipV(int isFlip);
    // void legacySetPwdAutoTrace(int nAuto);
    void legacySetTGCPositions(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8);
    // void legacySetiClear(int id);
    void legacyZoomColorROI(int xDirection, int yDirection);
    // // F means forward
    void legacyFProbeType(int pbPort, int pbType);
    // void legacySaveScuInitPara();
    void legacyStart();
    void legacyStop();
    // void legacyWifiEWM(const QString& fptStr, QString& htpStr);
private:
    int boolToIncrease(const bool& increase);
    int depthHardCode(const double &value);
    double mmToCm(const double &value);
};