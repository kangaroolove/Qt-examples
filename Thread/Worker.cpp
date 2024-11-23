#include "Worker.h"
#include <QDebug>
#include <QThread>

Worker::Worker(QObject *parent) : QObject(parent) {}

Worker::~Worker() {}

void Worker::doWork() {
  for (int i = 0; i < 100; ++i)
    qDebug() << "Worker currentThreadId() = " << QThread::currentThreadId()
             << ", i = " << i;
}