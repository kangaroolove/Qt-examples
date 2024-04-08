#pragma once

#include "Server.h"
#include "daqclib.h"

using Daqc = DAQCLib::DAQC;

struct BITMAPINFOHEADER {
    uint32_t biSize;
    int32_t  biWidth;
    int32_t  biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

struct RGBQUAD {
    uint8_t rgbBlue;
    uint8_t rgbGreen;
    uint8_t rgbRed;
    uint8_t rgbReserved;
};

struct BITMAPINFO {
    BITMAPINFOHEADER bmiHeader;
    RGBQUAD          bmiColors[256];
};

class QTimer;
class DaqcServer : public Server
{
    Q_OBJECT
public:
    DaqcServer(QObject* parent = nullptr);
    ~DaqcServer();
    void start() override;
protected:
    HandleReceiveMessageTask* generateHandleRequestTask(const QByteArray& data) override;
private slots:
    void frameReady();
    void updateTimerTimeout();
private:
    QJsonObject getDaqcInfo();

    Daqc* m_daqc;
    QTimer* m_DaqcInfoUpdateTimer;
};