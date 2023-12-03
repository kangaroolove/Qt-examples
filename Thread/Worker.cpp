#include "Worker.h"
#include <QThread>
#include <QDebug>

Worker::Worker(QObject* parent)
    : QObject(parent)
{

}

Worker::~Worker()
{

}

void Worker::doWork()
{
    for (int i = 0; i < 100; ++i)
        qDebug()<<"Worker QThread::currentThreadId() = "<<QThread::currentThreadId()<<", i = "<<i;
}