#include "ResourceManager.h"
#include "daqclib.h"
#include "DaqcClientDef.h"
#include <QReadWriteLock>
#include <QJsonObject>
#include <QVariant>
#include <QDebug>

bool ResourceManager::m_initialized = false;

ResourceManager::ResourceManager(QObject* parent) :
    QObject(parent),
    m_daqc(new Daqc()),
    m_readWriteLock(new QReadWriteLock)
{
    connect(m_daqc, SIGNAL(FrameReady()), this, SLOT(onFrameReady()));
}

ResourceManager::~ResourceManager()
{
    delete m_daqc;
}

ResourceManager *ResourceManager::getInstance()
{
    static ResourceManager resourceManager;
    return &resourceManager;
}

void ResourceManager::handleUpdate(const QString &parameter, const QVariant &valueTypes, const QVariant &values)
{
    // Before initialization, the server shouldn't do anything
    if (!m_initialized && parameter != DaqcParameter::INIT)
        return;

    auto valueList = values.toList();
    auto valueTypeList = valueTypes.toStringList();

    if (parameter == DaqcParameter::TEST)
        qInfo("Update Test");
    else if (parameter == DaqcParameter::INIT)
    {
        m_initialized = true;
        m_daqc->Init(valueList.first().toInt());
    }
    else if (parameter == DaqcParameter::F_PROBE_TYPE)
        m_daqc->fProbeType(valueList.first().toInt(), valueList.last().toInt());
    else if (parameter == DaqcParameter::PROBE_POS)
        m_daqc->SetProbePOS(valueList.first().toInt());
    else if (parameter == DaqcParameter::RADIUM)
        m_daqc->SetRadium(valueList.first().toDouble());
    else if (parameter == DaqcParameter::ESPIN)
        m_daqc->setEspin(valueList.first().toDouble());
    else if (parameter == DaqcParameter::EXAM_TYPE_ID)
        m_daqc->SetExamTypeID(valueList.first().toInt());
    else if (parameter == DaqcParameter::ACUI)
        m_daqc->SetACUI(valueList.first().toInt());
    else if (parameter == DaqcParameter::PWIF_BUFF_MS)
        m_daqc->setPwifBuffms(valueList.first().toInt());
    else if (parameter == DaqcParameter::SCAN_MODE)
        m_daqc->setScanMode(valueList.first().toInt());
    else if (parameter == DaqcParameter::REALTIME_EN)
        m_daqc->RealtimeEn(valueList.first().toInt());
    else if (parameter == DaqcParameter::START)
        m_daqc->start();
    else if (parameter == DaqcParameter::STOP)
        m_daqc->stop();
    else if (parameter == DaqcParameter::THI)
        m_daqc->SetTHI(valueList.first().toInt());
    else if (parameter == DaqcParameter::ZOOM_COLOR_ROI)
        m_daqc->ZoomColorROI(valueList.first().toInt(), valueList.last().toInt());
    else if (parameter == DaqcParameter::MOVE_ROI_COLOR)
        m_daqc->MoveROIColor(valueList.first().toInt(), valueList.last().toInt());
    else if (parameter == DaqcParameter::TGC_POSITIONS)
        m_daqc->SetTGCPositions(valueList.at(0).toInt(), valueList.at(1).toInt(), valueList.at(2).toInt(), valueList.at(3).toInt(), valueList.at(4).toInt(), valueList.at(5).toInt(), valueList.at(6).toInt(), valueList.at(7).toInt());
    else if (parameter == DaqcParameter::B_DYNAMIC)
        m_daqc->SetBDynamic(valueList.first().toInt());
    else if (parameter == DaqcParameter::D_DYNAMIC)
        m_daqc->SetDDynamic(valueList.first().toInt());
    else if (parameter == DaqcParameter::FLIP_H)
        m_daqc->SetFlipH(valueList.first().toInt());
    else if (parameter == DaqcParameter::FLIP_V)
        m_daqc->SetFlipV(valueList.first().toInt());
    else if (parameter == DaqcParameter::B_GAIN)
        m_daqc->SetBGain(valueList.first().toInt());
    else if (parameter == DaqcParameter::C_GAIN)
        m_daqc->SetCGain(valueList.first().toInt());
    else if (parameter == DaqcParameter::DEPTH)
        m_daqc->SetDepth(valueList.first().toInt());
    else if (parameter == DaqcParameter::B_FREQUENCY)
        m_daqc->SetFrequence(valueList.first().toInt());
    else if (parameter == DaqcParameter::B_FREQUENCY_2)
        m_daqc->SetFreq2(valueList.first().toInt());
    else if (parameter == DaqcParameter::PALETTE)
        m_daqc->Palette(valueList.first().toInt(), valueList.at(1).toInt(), valueList.last().toInt());
    else if (parameter == DaqcParameter::FAVG)
        m_daqc->SetFrameRelation(valueList.first().toInt());
    else if (parameter == DaqcParameter::LAVG)
        m_daqc->SetLineDensity(valueList.first().toInt());
    else if (parameter == DaqcParameter::CONTRAST)
        m_daqc->SetBDynamic(valueList.first().toInt());
    else if (parameter == DaqcParameter::C_PRF)
        m_daqc->SetCPRF(valueList.first().toInt());
    else if (parameter == DaqcParameter::D_PRF)
        m_daqc->SetDPRF(valueList.first().toInt());
    else if (parameter == DaqcParameter::C_WF)
        m_daqc->SetCWallFilterFreq(valueList.first().toInt());
    else if (parameter == DaqcParameter::D_WF)
        m_daqc->SetDWallFilterFreq(valueList.first().toInt());
    else if (parameter == DaqcParameter::SENSITIVITY)
        m_daqc->SetColorPrior(valueList.first().toInt());
    else if (parameter == DaqcParameter::SWING_ANGLE)
        m_daqc->SetROISwingAngle(valueList.first().toInt());
    else if (parameter == DaqcParameter::SV)
        m_daqc->SetPWDgateSize(valueList.first().toInt());
    else if (parameter == DaqcParameter::CA)
        m_daqc->SetPWDCorrectionAngle(valueList.first().toInt());
    else if (parameter == DaqcParameter::D_SPEED)
        m_daqc->SetDSpeed(valueList.first().toInt());
    else if (parameter == DaqcParameter::D_NOISE_REJECT)
        m_daqc->SetDNoiseRej(valueList.first().toInt());
    else if (parameter == DaqcParameter::D_SOUND_VOLUME)
        m_daqc->SetDSoundVolum(valueList.first().toInt());
    else if (parameter == DaqcParameter::COLOR_INVERT)
        m_daqc->SetColorInvert(valueList.first().toBool());
    else if (parameter == DaqcParameter::D_INVERT)
        m_daqc->SetPwdInvert(valueList.first().toBool());
    else if (parameter == DaqcParameter::C_AUTO_TRACE)
        m_daqc->setCAutoTrace(valueList.first().toBool());
    else if (parameter == DaqcParameter::D_AUTO_TRACE)
        m_daqc->SetPwdAutoTrace(valueList.first().toBool());
    else if (parameter == DaqcParameter::B_C_D_SYNCHRO)
        m_daqc->SetBCDSynChro(valueList.first().toInt());
    else if (parameter == DaqcParameter::ACUI_PARAMETER)
        m_daqc->FacuiParams(valueList.first().toInt(), valueList.last().toInt());
    else if (parameter == DaqcParameter::IMAGE_PROCESS)
        m_daqc->SetImageProcess(valueList.first().toInt());
    else if (parameter == DaqcParameter::MODE_2B)
        m_daqc->Mode2B();
    else if (parameter == DaqcParameter::D_BASELINE)
        m_daqc->SetDBaseLine(valueList.first().toInt());
}

void ResourceManager::onFrameReady()
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
    emit frameReady(image);
}

QJsonObject ResourceManager::getDaqcInfo()
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
    object[DaqcParameter::FPS] = m_daqc->GetFPS();

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
    object[DaqcParameter::PARAMETER_SEVEN] = m_daqc->GetParameter((int)WelldParameterId::PARAMETER_SEVEN);

    // offset for x axis of ROI for CD, D, M mode from Welld
    const int ROI_X_OFFSET = 180;
    object[DaqcParameter::ROI_POSITION_X] = m_daqc->scanMode() == (int)ScanMode::C_MODE ? m_daqc->GetParameter((int)WelldParameterId::C_ROI_X) : m_daqc->GetParameter((int)WelldParameterId::D_ROI_X) + ROI_X_OFFSET;
    object[DaqcParameter::ROI_POSITION_Y] = m_daqc->scanMode() == (int)ScanMode::C_MODE ? m_daqc->GetParameter((int)WelldParameterId::C_ROI_Y) : m_daqc->GetParameter((int)WelldParameterId::D_ROI_Y);

    return object;
}

