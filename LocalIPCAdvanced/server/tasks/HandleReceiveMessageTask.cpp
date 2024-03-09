#include "HandleReceiveMessageTask.h"

HandleReceiveMessageTask::HandleReceiveMessageTask(const QByteArray& data) :
    m_data(data)
{

}

HandleReceiveMessageTask::~HandleReceiveMessageTask()
{

}

void HandleReceiveMessageTask::run()
{
    analyzeJson(m_data);
}
