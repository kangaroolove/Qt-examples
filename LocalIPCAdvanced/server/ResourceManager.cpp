#include "ResourceManager.h"
#include "daqclib.h"
#include "DaqcClientDef.h"
#include <QReadWriteLock>
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
    
    QWriteLocker locker(m_readWriteLock);

    auto valueList = values.toList();
    auto valueTypeList = valueTypes.toStringList();

    if (valueList.size() != valueTypeList.size())
    {
        qCritical()<<"valueList and valueTypeList size are not matched";
        return;
    }

    qInfo()<<"Parameter = "<<parameter;
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

