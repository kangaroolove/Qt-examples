#pragma once

#include <QObject>

class ServerWorker : public QObject
{
    Q_OBJECT
public:
    ServerWorker();
    ~ServerWorker();
public slots:
    void handleUpdateRequest(const QString &parameter, const QVariant &valueTypes, const QVariant &values);
private:

};