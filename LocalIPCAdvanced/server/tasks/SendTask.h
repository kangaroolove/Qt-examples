#pragma once

#include <QRunnable>

class SendTask : public QRunnable
{
public:
    SendTask();
    ~SendTask();
    void run() override;
private:

};