#pragma once

#include "HandleRequestTask.h"

class DaqcHandleRequestTask : public HandleRequestTask
{
public:
    DaqcHandleRequestTask(const QByteArray& data);
    ~DaqcHandleRequestTask();
protected:
    void analyzeJson(const QByteArray& data) override;
private:
    void handleTask(const QString& api);
};