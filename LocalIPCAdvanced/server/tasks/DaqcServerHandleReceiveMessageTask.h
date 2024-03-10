#pragma once

#include "HandleReceiveMessageTask.h"
#include <QObject>

class Server;
class QJsonDocument;

class DaqcServerHandleReceiveMessageTask : public QObject, public HandleReceiveMessageTask
{
    Q_OBJECT
public:
    DaqcServerHandleReceiveMessageTask(Server* server, const QByteArray& data);
    ~DaqcServerHandleReceiveMessageTask();
protected:
    void analyzeJson(const QByteArray& data) override;
private:
    void handleUpdateRequest(const QString& parameter, const QString& valueType, const QVariant& value);
    QString getRequestType(const QJsonDocument& document);
    QString getClientMessageId(const QJsonDocument& document);
    QString getParameter(const QJsonDocument& document);
    QString getValueType(const QJsonDocument& document);
    QVariant getValue(const QJsonDocument& document);

    Server* m_server;
};