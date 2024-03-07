#pragma once

#include "HandleReceiveMessageTask.h"

class Server;
class QJsonDocument;

class DaqcServerHandleReceiveMessageTask : public HandleReceiveMessageTask
{
public:
    DaqcServerHandleReceiveMessageTask(Server* server, const QByteArray& data);
    ~DaqcServerHandleReceiveMessageTask();
protected:
    void analyzeJson(const QByteArray& data) override;
private:
    void handleTask(const QString& parameter, const QString& requestType, const QString& clientMessageId);
    QString getRequestType(const QJsonDocument& document);
    QString getClientMessageId(const QJsonDocument& document);
    QString getParameter(const QJsonDocument& document);

    Server* m_server;
};