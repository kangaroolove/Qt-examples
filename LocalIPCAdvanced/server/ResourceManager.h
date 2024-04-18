#pragma once

#include "daqclib.h"
#include <QObject>

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

using Daqc = DAQCLib::DAQC;

class QReadWriteLock;
class ResourceManager : public QObject
{
    Q_OBJECT
public:
    static ResourceManager* getInstance();
    void handleUpdate(const QString &parameter, const QVariant &valueTypes, const QVariant &values);
    QJsonObject getDaqcInfo();
    QJsonObject getImageCurrentChannel();
signals:
    void frameReady(const QImage& image);
private slots:
    void onFrameReady();
private:
    ResourceManager(QObject* parent = nullptr);
    ~ResourceManager();

    Daqc* m_daqc;
    QReadWriteLock* m_readWriteLock;
    static bool m_initialized;
    QImage m_image;
};