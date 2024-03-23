#pragma once

#include "HandleReceiveMessageTask.h"
#include "daqclib.h"
#include <QObject>

using Daqc = DAQCLib::DAQC;

class Server;
class QJsonDocument;

class DaqcServerHandleReceiveMessageTask : public HandleReceiveMessageTask
{
public:
    DaqcServerHandleReceiveMessageTask(Server* server, Daqc* daqc, const QByteArray& data);
    ~DaqcServerHandleReceiveMessageTask();
protected:
    void analyzeJson(const QByteArray& data) override;
private:
    void handleUpdateRequest(const QString& parameter, const QVariant& valueTypes, const QVariant& values);
    void handleGetRequest(const QString& parameter, const QVariant& valueTypes, const QVariant& values, const QString& messageId);
    QString getRequestType(const QJsonDocument& document) const;
    QString getPacketType(const QJsonDocument& document) const;

    Server* m_server;
    Daqc* m_daqc;
};