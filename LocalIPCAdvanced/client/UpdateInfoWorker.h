#pragma once

#include <QObject>

class DaqcClient;
class QTimer;

class UpdateInfoWorker : public QObject
{
    Q_OBJECT
public:
    UpdateInfoWorker(DaqcClient* client, QObject* parent = nullptr);
    ~UpdateInfoWorker();
public slots:
    void startUpdate();
private slots:
    void updateInfoFromServer();
private:
    DaqcClient* m_client;
    QTimer* m_timer;
};