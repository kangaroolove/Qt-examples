#include "Widget.h"

#include <QDebug>
#include <QThread>

#include "Worker.h"

Widget::Widget(QWidget *parent) : QWidget(parent), m_thread(new QThread(this)) {
    initWorker();
    print();
}

Widget::~Widget() {
    m_thread->quit();
    m_thread->wait();
}

void Widget::initWorker() {
    Worker *worker = new Worker;
    worker->moveToThread(m_thread);

    connect(m_thread, &QThread::finished, worker, &Worker::deleteLater);
    connect(this, &Widget::doWork, worker, &Worker::doWork);
    m_thread->start();

    emit doWork();
}

void Widget::print() {
    for (int i = 0; i < 100; ++i)
        qDebug() << "main currentThreadId() = " << QThread::currentThreadId()
                 << ", i = " << i;
}
