#pragma once

#include <QRunnable>

class HandleRequestTask : public QRunnable
{
public:
    HandleRequestTask();
    ~HandleRequestTask();
    void run() override;
protected:
    virtual bool analyzeJson(const QByteArray& data) = 0;
private:

};