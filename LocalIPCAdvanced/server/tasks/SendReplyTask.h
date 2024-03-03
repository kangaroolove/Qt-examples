#pragma once

#include <QRunnable>

class SendReplyTask : public QRunnable
{
public:
    SendReplyTask();
    ~SendReplyTask();
    void run() override;
private:

};