#pragma once

#include "HandleReceiveMessageTask.h"
#include <QObject>

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
    void handleUpdateRequest(const QString& parameter, const QVariant& valueTypes, const QVariant& values);
    QString getRequestType(const QJsonDocument& document) const;
    QString getPacketType(const QJsonDocument& document) const;

    Server* m_server;
};