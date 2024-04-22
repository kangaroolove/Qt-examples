#include "SimpleTask.h"
#include <QDebug>

SimpleTask::SimpleTask(const int &id) :
    m_id(id)
{

}

SimpleTask::~SimpleTask()
{

}

void SimpleTask::run()
{
    qDebug()<<"id = "<<m_id;
}
