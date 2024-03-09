#pragma once

#include "HandleReceiveMessageTask.h"
#include <QObject>

class Server;
class QJsonDocument;
class PacketFactory;

class DaqcServerHandleReceiveMessageTask : public QObject, public HandleReceiveMessageTask
{
    Q_OBJECT
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
    PacketFactory* m_packetFactory;
};