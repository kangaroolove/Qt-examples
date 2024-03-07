#pragma once

#include "HandleRequestTask.h"

class Server;
class QJsonDocument;

class DaqcHandleRequestTask : public HandleRequestTask
{
public:
    DaqcHandleRequestTask(Server* server, const QByteArray& data);
    ~DaqcHandleRequestTask();
protected:
    void analyzeJson(const QByteArray& data) override;
private:
    void handleTask(const QString& parameter, const QString& requestType, const QString& clientMessageId);
    QString getRequestType(const QJsonDocument& document);
    QString getClientMessageId(const QJsonDocument& document);
    QString getParameter(const QJsonDocument& document);

    Server* m_server;
};