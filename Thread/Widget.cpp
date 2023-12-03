#include "Widget.h"
#include "Worker.h"
#include "WorkerThread.h"
#include <QThread>
#include <QDebug>

Widget::Widget(QWidget * parent)
    : QWidget(parent)
    , m_thread(new QThread(this))
    , m_workerThread(new WorkerThread(this))
{
    initWorker();
    initWorkerThread();
    print();
}

Widget::~Widget()
{
    m_thread->quit();
    m_thread->wait();
}

void Widget::initWorker()
{
    Worker* worker = new Worker;
    worker->moveToThread(m_thread);

    connect(m_thread, &QThread::finished, worker, &Worker::deleteLater);
    connect(this, &Widget::doWork, worker, &Worker::doWork);
    m_thread->start();

    emit doWork();
}

void Widget::print()
{
    for (int i = 0; i < 100; ++i)
        qDebug()<<"main currentThreadId() = "<<QThread::currentThreadId()<<", i = "<<i;
}

void Widget::initWorkerThread()
{
    m_workerThread->start();
}
