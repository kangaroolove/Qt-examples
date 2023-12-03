#pragma once

#include <QObject>

class Worker : public QObject
{
public:
    Worker(QObject* parent = nullptr);
    ~Worker();
public slots:
    void doWork();
};