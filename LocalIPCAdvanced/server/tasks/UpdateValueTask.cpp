#include "UpdateValueTask.h"
#include <QDebug>

QReadWriteLock UpdateValueTask::m_readWriteLock;

UpdateValueTask::UpdateValueTask(const UpdateValueInfo& updateValueInfo) :
    m_updateValueInfo(updateValueInfo)
{

}

UpdateValueTask::~UpdateValueTask()
{

}

void UpdateValueTask::run()
{
    QWriteLocker locker(&m_readWriteLock);
    if (m_updateValueInfo.parameter == "test")
    {
        qDebug()<<m_updateValueInfo.parameter<<" has set value:10";
    }
}
