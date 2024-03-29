#include "UpdateValueTask.h"
#include "StringDef.h"
#include <QDebug>

QReadWriteLock UpdateValueTask::m_readWriteLock;

UpdateValueTask::UpdateValueTask(const UpdateValueInfo& updateValueInfo, Daqc* daqc) :
    m_updateValueInfo(updateValueInfo),
    m_daqc(daqc)
{

}

UpdateValueTask::~UpdateValueTask()
{

}

void UpdateValueTask::run()
{
    QWriteLocker locker(&m_readWriteLock);

    auto values = m_updateValueInfo.values.toList();
    auto valueTypes = m_updateValueInfo.valueTypes.toStringList();

    if (values.isEmpty())
    {
        qCritical()<<"values is empty";
        return;
    }

    if (values.size() != valueTypes.size())
    {
        qCritical()<<"values and valueTypes size are not matched";
        return;
    }

    if (m_updateValueInfo.parameter == "test")
    {
        qDebug()<<m_updateValueInfo.parameter<<" has set value:10";

        for (auto &value : values)
            qDebug()<<"value = "<<value;

        for (auto &type : valueTypes)
            qDebug()<<"valueType = "<<type;
    }
    else if (m_updateValueInfo.parameter == DaqcParameter::INIT)
        m_daqc->Init(values.first().toInt());
    else if (m_updateValueInfo.parameter == DaqcParameter::F_PROBE_TYPE)
        m_daqc->fProbeType(values.first().toInt(), values.last().toInt());
    else if (m_updateValueInfo.parameter == DaqcParameter::PROBE_POS)
        m_daqc->SetProbePOS(values.first().toInt());
    else if (m_updateValueInfo.parameter == DaqcParameter::RADIUM)
        m_daqc->SetRadium(values.first().toDouble());
    else if (m_updateValueInfo.parameter == DaqcParameter::ESPIN)
        m_daqc->setEspin(values.first().toDouble());
    else if (m_updateValueInfo.parameter == DaqcParameter::EXAM_TYPE_ID)
        m_daqc->SetExamTypeID(values.first().toInt());
    else if (m_updateValueInfo.parameter == DaqcParameter::ACUI)
        m_daqc->SetACUI(values.first().toInt());
    else if (m_updateValueInfo.parameter == DaqcParameter::PWIF_BUFF_MS)
        m_daqc->setPwifBuffms(values.first().toInt());
    else if (m_updateValueInfo.parameter == DaqcParameter::SCAN_MODE)
        m_daqc->setScanMode(values.first().toInt());
    else if (m_updateValueInfo.parameter == DaqcParameter::REALTIME_EN)
        m_daqc->RealtimeEn(values.first().toInt());
    else if (m_updateValueInfo.parameter == DaqcParameter::START)
        m_daqc->start();
    else if (m_updateValueInfo.parameter == DaqcParameter::STOP)
        m_daqc->stop();
    else if (m_updateValueInfo.parameter == DaqcParameter::THI)
        m_daqc->SetTHI(values.first().toInt());
    else if (m_updateValueInfo.parameter == DaqcParameter::ZOOM_COLOR_ROI)
        m_daqc->ZoomColorROI(values.first().toInt(), values.last().toInt());
    else if (m_updateValueInfo.parameter == DaqcParameter::MOVE_ROI_COLOR)
        m_daqc->MoveROIColor(values.first().toInt(), values.last().toInt());
    else if (m_updateValueInfo.parameter == DaqcParameter::TGC_POSITIONS)
        m_daqc->SetTGCPositions(values.at(0).toInt(), values.at(1).toInt(), values.at(2).toInt(), values.at(3).toInt(), values.at(4).toInt(), values.at(5).toInt(), values.at(6).toInt(), values.at(7).toInt());
    else if (m_updateValueInfo.parameter == DaqcParameter::B_DYNAMIC)
        m_daqc->SetBDynamic(values.first().toInt());
    else if (m_updateValueInfo.parameter == DaqcParameter::D_DYNAMIC)
        m_daqc->SetDDynamic(values.first().toInt());
    else if (m_updateValueInfo.parameter == DaqcParameter::FLIP_H)
        m_daqc->SetFlipH(values.first().toInt());
    else if (m_updateValueInfo.parameter == DaqcParameter::FLIP_V)
        m_daqc->SetFlipV(values.first().toInt());
    else if (m_updateValueInfo.parameter == DaqcParameter::B_GAIN)
        m_daqc->SetBGain(values.first().toInt());
    else if (m_updateValueInfo.parameter == DaqcParameter::C_GAIN)
        m_daqc->SetCGain(values.first().toInt());
    else if (m_updateValueInfo.parameter == DaqcParameter::DEPTH)
        m_daqc->SetDepth(values.first().toInt());
    else if (m_updateValueInfo.parameter == DaqcParameter::B_FREQUENCY)
        m_daqc->SetFrequence(values.first().toInt());
    else if (m_updateValueInfo.parameter == DaqcParameter::B_FREQUENCY_2)
        m_daqc->SetFreq2(values.first().toInt());
    else if (m_updateValueInfo.parameter == DaqcParameter::CHROMA)
        ;
    else if (m_updateValueInfo.parameter == DaqcParameter::PALETTE)
    {
        QPalette palette;
        m_daqc->setPalette(palette);
    }
    else if (m_updateValueInfo.parameter == DaqcParameter::FAVG)
        m_daqc->SetFrameRelation(values.first().toInt());
    else if (m_updateValueInfo.parameter == DaqcParameter::LAVG)
        m_daqc->SetLineDensity(values.first().toInt());
    else if (m_updateValueInfo.parameter == DaqcParameter::CONTRAST)
        ;
    else if (m_updateValueInfo.parameter == DaqcParameter::C_PRF)
        m_daqc->SetCPRF(values.first().toInt());
    else if (m_updateValueInfo.parameter == DaqcParameter::D_PRF)
        m_daqc->SetDPRF(values.first().toInt());
    
}
