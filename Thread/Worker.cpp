#include "Worker.h"
#include <QDebug>
#include <QThread>

Worker::Worker(QObject *parent) : QObject(parent) {}

Worker::~Worker() {}

/**
 * @brief Any sub-thread functions must be slot functions and we must use
 * signals and slots to call funtions rather than worker->func() because
 * there will be a race condition.
 *
 * Here is from Qt document
 * Unlike queued slots or invoked methods, methods called directly on the
 * QThread object will execute in the thread that calls the method. When
 * subclassing QThread, keep in mind that the constructor executes in the
 * old thread while run() executes in the new thread. If a member variable
 * is accessed from both functions, then the variable is accessed from two
 * different threads. Check that it is safe to do so.
 *
 */
void Worker::doWork() {
    for (int i = 0; i < 100; ++i)
        qDebug() << "Worker currentThreadId() = " << QThread::currentThreadId()
                 << ", i = " << i;
}