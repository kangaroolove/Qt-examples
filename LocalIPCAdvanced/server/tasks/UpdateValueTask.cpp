#include "UpdateValueTask.h"
#include <QDebug>

UpdateValueTask::UpdateValueTask(const UpdateValueInfo& updateValueInfo) :
    m_updateValueInfo(updateValueInfo)
{

}

UpdateValueTask::~UpdateValueTask()
{

}

void UpdateValueTask::run()
{
    if (m_updateValueInfo.parameter == "test")
    {
        qDebug()<<m_updateValueInfo.parameter<<" has set value:10";
    }
}
