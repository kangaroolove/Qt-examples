#pragma once

#include <QRunnable>

class HandleRequestTask : public QRunnable
{
public:
    HandleRequestTask();
    ~HandleRequestTask();
    void run() override;
private:

};