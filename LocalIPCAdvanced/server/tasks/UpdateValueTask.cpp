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
    else if (m_updateValueInfo.parameter == INIT)
    {
        m_daqc->Init(values.first().toInt());
    }
}
