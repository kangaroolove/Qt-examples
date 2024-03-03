#pragma once

#include "HandleRequestTask.h"

class DaqcHandleRequestTask : public HandleRequestTask
{
public:
    DaqcHandleRequestTask();
    ~DaqcHandleRequestTask();
protected:
    bool analyzeJson(const QByteArray& data) override;
private:

};