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
    DaqcServerHandleReceiveMessageTask(Daqc* daqc, const QByteArray& data);
    ~DaqcServerHandleReceiveMessageTask();
signals:
    void stopSendFrame(bool stop);
protected:
    void analyzeJson(const QByteArray& data) override;
private:
    void handleUpdateRequest(const QString& parameter, const QVariant& valueTypes, const QVariant& values);
    QString getRequestType(const QJsonDocument& document) const;
    QString getPacketType(const QJsonDocument& document) const;

    Daqc* m_daqc;
};