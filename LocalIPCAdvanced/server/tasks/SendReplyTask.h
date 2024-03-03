#pragma once

#include "SendTask.h"

class SendReplyTask : public SendTask
{
public:
    SendReplyTask();
    ~SendReplyTask();
    void run() override;
private:

};