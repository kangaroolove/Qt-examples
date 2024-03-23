#include "DaqcServer.h"
#include "DaqcServerHandleReceiveMessageTask.h"
#include "SendTask.h"
#include "FramePacket.h"
#include <QThreadPool>
#include <QDebug>

DaqcServer::DaqcServer(QObject* parent) :
    Server(parent),
    m_daqc(new Daqc())
{
    connect(m_daqc, SIGNAL(FrameReady()), this, SLOT(frameReady()));
}

DaqcServer::~DaqcServer()
{
    delete m_daqc;
}

void DaqcServer::start()
{
    auto result = listen("Daqc");
    if (result)
        qDebug()<<"Daqc server started";
    else 
        qCritical()<<"Daqc server started failed";
}

HandleReceiveMessageTask *DaqcServer::generateHandleRequestTask(const QByteArray& data)
{
    return new DaqcServerHandleReceiveMessageTask(this, m_daqc, data);
}

void DaqcServer::frameReady()
{
    BITMAPINFO* bmi = (BITMAPINFO*)m_daqc->GetpBMIInfo();
    int width = bmi->bmiHeader.biWidth;
    int height = bmi->bmiHeader.biHeight;
    QImage image((uchar*)m_daqc->GetpDIBits(), width, height, QImage::Format_Indexed8);
    QVector<QRgb> colorTable(256);
    for (int i = 0; i < 256; i++)
        colorTable[i] = qRgb(
            bmi->bmiColors[i].rgbRed,
            bmi->bmiColors[i].rgbGreen,
            bmi->bmiColors[i].rgbBlue);
    image.setColorTable(colorTable);

    FramePacket* packet = new FramePacket(image);
    QThreadPool::globalInstance()->start(new SendTask(this, packet));
}