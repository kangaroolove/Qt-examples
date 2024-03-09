#pragma once

#include <QObject>
#include <functional>
#include <QVariant>

class QThread;
class Client;
class QEventLoop;
class Packet;

class DaqcClient : public QObject
{
    Q_OBJECT
public:
    DaqcClient(QObject* parent = nullptr);
    ~DaqcClient();
    void start();
    int testGetApi();
    void testSetApi(bool isTest);
    // get functions
    double getRegionPhysicalDeltaX();
    double getRegionPhysicalDeltaY();
    int getBGain();
    int getCGain();
    int getMGain();
    double getXmlDepth();
    int getDepthMm();
    double getDepthCm();
    double getBFrequency();
    double getBFrequency2();
    double getMFrequency();
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
    int getMSpeed();
    int getNoiseReject();
    int getAudio();
    int getBaseline();
    int getRotation();
    double getSpacingX();
    double getSpacingY();
    bool isBb();
    bool isUp();
    bool isThi();
    bool isCenterLine();
    bool isRoiSite();
    bool isRoiSize();
    bool isCInvert();
    bool isDInvert();
    bool isCAutoTrace();
    bool isDAutoTrace();
    bool isUpdate();
    bool isSynchro();
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
signals:
    void sendMessage(const QByteArray& msg);
    void connectServer();
    void receiveMessage(const QByteArray& msg);
private:
    QVariant createGetRequest(std::function<Packet*()> callback);
    void createUpdateRequest(Packet* packet);
    int boolToIncrease(const bool& increase);

    QThread* m_thread;
    Client* m_client;
};