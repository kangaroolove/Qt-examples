#include "DaqcServer.h"
#include "DaqcServerHandleReceiveMessageTask.h"
#include "SendTask.h"
#include "FramePacket.h"
#include "ReplyPacket.h"
#include "DaqcClientDef.h"
#include "GetPacket.h"
#include <QThreadPool>
#include <QDebug>
#include <QTimer>

DaqcServer::DaqcServer(QObject* parent) :
    Server(parent),
    m_daqc(new Daqc())
{
    connect(m_daqc, SIGNAL(FrameReady()), this, SLOT(frameReady()));

    QTimer* timer = new QTimer(this);
    timer->setInterval(3000);
    connect(timer, &QTimer::timeout, this, [this]{
        QImage image("D:/2.png");
        QJsonObject object;
        object[DaqcParameter::TEST] = 10;
        object[DaqcParameter::B_GAIN] = 0.5;
        GetPacket* packet = new GetPacket(object, image);
        QThreadPool::globalInstance()->start(new SendTask(this, packet));
    });
    timer->start();
}

DaqcServer::~DaqcServer()
{
    delete m_daqc;
}

void DaqcServer::start()
{
    auto result = listen("Daqc");
    if (result)
        qInfo()<<"Daqc server started";
    else 
        qCritical()<<"Daqc server started failed";
}

HandleReceiveMessageTask *DaqcServer::generateHandleRequestTask(const QByteArray& data)
{
    return new DaqcServerHandleReceiveMessageTask(this, m_daqc, data);
}

void DaqcServer::sendImageCurrentChannel()
{
    ReplyPacketInfo info;
    info.parameter = DaqcParameter::IMAGE_CURRENT_CHANNEL;
    info.value = (int)m_daqc->GetParameter((int)WelldParameterId::IMAGE_CURRENT_CHANNEL);
    info.valueType = "int";
    info.requestType = "get";
    ReplyPacket* packet = new ReplyPacket(info);
    QThreadPool::globalInstance()->start(new SendTask(this, packet));
}

void DaqcServer::sendFrame()
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

void DaqcServer::frameReady()
{
    sendFrame();
}