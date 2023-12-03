#include "WorkerThread.h"
#include <QDebug>

WorkerThread::WorkerThread(QObject* parent)
    : QThread(parent)
    , m_finishThread(false)
{

}

WorkerThread::~WorkerThread()
{
    m_finishThread = true;
    this->quit();
    this->wait();
}

void WorkerThread::run()
{
    //while (!m_finishThread)
        for (int i = 0; i < 100; ++i)
            qDebug()<<"WorkerThread currentThreadId() = "<<QThread::currentThreadId()<<", i = "<<i;
}
