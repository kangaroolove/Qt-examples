#pragma once

#include "Server.h"

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
class ServerWorker;
class QThread;
class DaqcServer : public Server
{
    Q_OBJECT
public:
    DaqcServer(QObject* parent = nullptr);
    ~DaqcServer();
    void start() override;
signals:
    void handleUpdateRequest(const QString &parameter, const QVariant &valueTypes, const QVariant &values);
protected:
    HandleReceiveMessageTask* generateHandleRequestTask(const QByteArray& data) override;
    void handleReceive(const QByteArray& data) override;
private slots:
    void frameReady();
private:
    QJsonObject getDaqcInfo();
    QString getPacketType(const QJsonDocument &document) const;
    QString getRequestType(const QJsonDocument &document) const;

    ServerWorker* m_worker;
    QThread* m_thread;
};