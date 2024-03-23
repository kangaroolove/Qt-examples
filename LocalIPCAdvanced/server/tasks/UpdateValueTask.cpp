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
}
