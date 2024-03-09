#pragma once

#include <QRunnable>
#include <QByteArray>
#include <QObject>
class HandleReceiveMessageTask : public QRunnable
{
public:
    HandleReceiveMessageTask(const QByteArray& data);
    ~HandleReceiveMessageTask();
    void run() override;
protected:
    virtual void analyzeJson(const QByteArray& data) = 0;
private:
    QByteArray m_data;
};