#pragma once

#include <QObject>
#include <QSharedMemory>

class ServerWorker : public QObject
{
    Q_OBJECT
public:
    ServerWorker();
    ~ServerWorker();
signals:
    void uploadImageFinished();
public slots:
    void handleUpdateRequest(const QString &parameter, const QVariant &valueTypes, const QVariant &values);
    void frameReady(const QImage& image);
private:
    QSharedMemory* m_sharedMemory;
};