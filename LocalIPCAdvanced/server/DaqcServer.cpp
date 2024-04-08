#include "DaqcServer.h"
#include "DaqcServerHandleReceiveMessageTask.h"
#include "SendTask.h"
#include "DaqcClientDef.h"
#include "GetPacket.h"
#include <QThreadPool>
#include <QDebug>
#include <QTimer>

DaqcServer::DaqcServer(QObject* parent) :
    Server(parent),
    m_daqc(new Daqc()),
    m_DaqcInfoUpdateTimer(new QTimer(this))
{
    m_DaqcInfoUpdateTimer->setInterval(400);
    connect(m_DaqcInfoUpdateTimer, &QTimer::timeout, this, &DaqcServer::updateTimerTimeout);
    connect(m_daqc, SIGNAL(FrameReady()), this, SLOT(frameReady()));

    m_DaqcInfoUpdateTimer->start();
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
    return new DaqcServerHandleReceiveMessageTask(m_daqc, data);
}

void DaqcServer::updateTimerTimeout()
{
    GetPacket* packet = new GetPacket(getDaqcInfo());
    QThreadPool::globalInstance()->start(new SendTask(this, packet));
}

QJsonObject DaqcServer::getDaqcInfo()
{
    QJsonObject object;
    object[DaqcParameter::TEST] = 10;

    object[DaqcParameter::THI] = m_daqc->THI();
    object[DaqcParameter::C_BASE_LINE] = m_daqc->CBaseLine();
    object[DaqcParameter::SCAN_MODE] = m_daqc->scanMode();
    object[DaqcParameter::B_DYNAMIC] = m_daqc->BDynamic();
    object[DaqcParameter::D_DYNAMIC] = m_daqc->DDynamic();
    object[DaqcParameter::PERSISTENCE_COLOR] = m_daqc->PersistenceColor();
    object[DaqcParameter::PROBE_SEL] = m_daqc->ProbeSEL();

    double regionPhysicalDeltaX = 0;
    double regionPhysicalDeltaY = 0;
    m_daqc->GetRegionPhysicalDelta(regionPhysicalDeltaX, regionPhysicalDeltaY);

    object[DaqcParameter::REGION_PHYSICAL_DELTA_X] = regionPhysicalDeltaX;
    object[DaqcParameter::REGION_PHYSICAL_DELTA_Y] = regionPhysicalDeltaY;
    object[DaqcParameter::B_GAIN] = m_daqc->BGain();
    object[DaqcParameter::C_GAIN] = m_daqc->CGain();
    object[DaqcParameter::B_FREQUENCY] = m_daqc->Frequence();
    object[DaqcParameter::B_FREQUENCY_2] = m_daqc->Freq2();
    object[DaqcParameter::FAVG] = m_daqc->FrameRelation();
    object[DaqcParameter::LAVG] = m_daqc->LavgRelation();
    object[DaqcParameter::C_PRF] = m_daqc->CPRF();
    object[DaqcParameter::D_PRF] = m_daqc->DPRF();
    object[DaqcParameter::C_WF] = m_daqc->CWallFilterFreq();
    object[DaqcParameter::D_WF] = m_daqc->DWallFilterFreq();
    object[DaqcParameter::SENSITIVITY] = m_daqc->ColorPrior();
    object[DaqcParameter::SWING_ANGLE] = m_daqc->ROISwingAngle();
    object[DaqcParameter::SV] = m_daqc->PWDgateSize();

    double ca = m_daqc->PWDCorrectionAngle();
    if (ca > 180)
        ca -= 180;
    ca = 90 - ca;
    object[DaqcParameter::CA] = ca;

    object[DaqcParameter::D_SPEED] = m_daqc->DSpeed();
    object[DaqcParameter::D_NOISE_REJECT] = m_daqc->DNoiseRej();
    object[DaqcParameter::D_SOUND_VOLUME] = m_daqc->DSoundVolum();
    object[DaqcParameter::COLOR_INVERT] = m_daqc->ColorInvert();
    object[DaqcParameter::D_INVERT] = m_daqc->PwdInvert();
    object[DaqcParameter::C_AUTO_TRACE] = m_daqc->cAutoTrace();
    object[DaqcParameter::B_C_D_SYNCHRO] = m_daqc->BCDSynChro();
    object[DaqcParameter::D_BASELINE] = m_daqc->DBaseLine();
    object[DaqcParameter::ACUI] = m_daqc->ACUI();
    object[DaqcParameter::DUAL_MODE] = m_daqc->GetParameter((int)WelldParameterId::REALTIME_EN);
    object[DaqcParameter::SPACING_X] = m_daqc->GetParameter((int)WelldParameterId::SPACING_X);
    object[DaqcParameter::SPACING_Y] = m_daqc->GetParameter((int)WelldParameterId::SPACING_Y);
    object[DaqcParameter::IMAGE_CURRENT_CHANNEL] = m_daqc->GetParameter((int)WelldParameterId::IMAGE_CURRENT_CHANNEL);
    object[DaqcParameter::XML_DEPTH] = m_daqc->GetParameter((int)WelldParameterId::XML_DEPTH);
    object[DaqcParameter::PARAMETER_SIX] = m_daqc->GetParameter((int)WelldParameterId::PARAMETER_SIX);

    // offset for x axis of ROI for CD, D, M mode from Welld
    const int ROI_X_OFFSET = 180;
    object[DaqcParameter::ROI_POSITION_X] = m_daqc->scanMode() == (int)ScanMode::C_MODE ? m_daqc->GetParameter((int)WelldParameterId::C_ROI_X) : m_daqc->GetParameter((int)WelldParameterId::D_ROI_X) + ROI_X_OFFSET;
    object[DaqcParameter::ROI_POSITION_Y] = m_daqc->scanMode() == (int)ScanMode::C_MODE ? m_daqc->GetParameter((int)WelldParameterId::C_ROI_Y) : m_daqc->GetParameter((int)WelldParameterId::D_ROI_Y);

    return object;
}

QJsonObject DaqcServer::getImageCurrentChannel()
{
    QJsonObject object;
    object[DaqcParameter::IMAGE_CURRENT_CHANNEL] = m_daqc->GetParameter((int)WelldParameterId::IMAGE_CURRENT_CHANNEL);
    return object;
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

    GetPacket* packet = new GetPacket(getImageCurrentChannel(), image);
    QThreadPool::globalInstance()->start(new SendTask(this, packet));
}