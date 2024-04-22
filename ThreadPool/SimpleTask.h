#pragma once

#include <QRunnable>

class SimpleTask : public QRunnable
{
public:
    SimpleTask(const int& id);
    ~SimpleTask();
    void run() override;
private:
    int m_id;
};