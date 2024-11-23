#pragma once

#include <QWidget>

class QThread;
class WorkerThread;

class Widget : public QWidget {
  Q_OBJECT
public:
  Widget(QWidget *parent = nullptr);
  ~Widget();
signals:
  void doWork();

private:
  void initWorker();
  void print();
  void initWorkerThread();

  QThread *m_thread;
  WorkerThread *m_workerThread;
};