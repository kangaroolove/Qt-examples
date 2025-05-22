#pragma once

#include <QThread>

class WorkerThread : public QThread {
    Q_OBJECT
public:
    WorkerThread(QObject *parent = nullptr);
    ~WorkerThread();

protected:
    void run() override;

private:
    bool m_finishThread;
};