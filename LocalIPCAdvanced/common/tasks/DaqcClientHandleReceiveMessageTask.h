#pragma once

#include "HandleReceiveMessageTask.h"
#include <QObject>
#include <QString>

class Client;

class DaqcClientHandleReceiveMessageTask : public QObject, public HandleReceiveMessageTask
{
    Q_OBJECT
public:
    DaqcClientHandleReceiveMessageTask(Client* client, const QByteArray& data);
    ~DaqcClientHandleReceiveMessageTask();
signals:
    void quitEventLoop(const QString& messageId);
protected:
    void analyzeJson(const QByteArray& data) override;

    Client* m_client;
};