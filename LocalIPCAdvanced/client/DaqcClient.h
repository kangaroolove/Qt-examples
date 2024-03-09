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
signals:
    void sendMessage(const QByteArray& msg);
    void connectServer();
    void receiveMessage(const QByteArray& msg);
private:
    QVariant createGetRequest(std::function<Packet*()> callback);
    void createUpdateRequest(Packet* packet);

    QThread* m_thread;
    Client* m_client;
};