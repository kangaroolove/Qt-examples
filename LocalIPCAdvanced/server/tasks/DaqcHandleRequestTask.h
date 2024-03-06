#pragma once

#include "HandleRequestTask.h"

class QJsonDocument;

class DaqcHandleRequestTask : public HandleRequestTask
{
public:
    DaqcHandleRequestTask(const QByteArray& data);
    ~DaqcHandleRequestTask();
protected:
    void analyzeJson(const QByteArray& data) override;
private:
    void handleTask(const QString& api);
    QString getRequestType(const QJsonDocument& document);
    QString getMessageId(const QJsonDocument& document);
    QString getParameter(const QJsonDocument& document);
};