#pragma once

#include "daqclib.h"
#include <QRunnable>
#include <QString>
#include <QVariant>
#include <QReadWriteLock>

using Daqc = DAQCLib::DAQC;

class UpdateValueInfo
{
public:
    QString parameter;
    QVariant valueTypes;
    QVariant values;
};

class UpdateValueTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    UpdateValueTask(const UpdateValueInfo& updateValueInfo, Daqc* daqc);
    ~UpdateValueTask();
    void run() override;
signals:
    void stopSendFrame(bool stop);
private:
    UpdateValueInfo m_updateValueInfo;
    static QReadWriteLock m_readWriteLock;
    Daqc* m_daqc;
};