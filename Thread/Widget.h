#pragma once

#include <QWidget>

class QThread;

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget* parent = nullptr);
    ~Widget();
signals:
    void doWork();
private:
    void initWorker();
    void print();

    QThread* m_thread;
};