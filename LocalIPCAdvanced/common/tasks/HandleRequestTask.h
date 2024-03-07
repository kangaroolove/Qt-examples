#pragma once

#include <QRunnable>
#include <QByteArray>

class HandleRequestTask : public QRunnable
{
public:
    HandleRequestTask(const QByteArray& data);
    ~HandleRequestTask();
    void run() override;
protected:
    virtual void analyzeJson(const QByteArray& data) = 0;
private:
    QByteArray m_data;
};