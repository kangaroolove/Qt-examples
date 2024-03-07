#include "HandleRequestTask.h"

HandleRequestTask::HandleRequestTask(const QByteArray& data) :
    m_data(data)
{

}

HandleRequestTask::~HandleRequestTask()
{

}

void HandleRequestTask::run()
{
    analyzeJson(m_data);
}
