#pragma once

#include "daqclib.h"
#include <QObject>

using Daqc = DAQCLib::DAQC;

class QReadWriteLock;
class ResourceManager : public QObject
{
    Q_OBJECT
public:
    static ResourceManager* getInstance();
    void handleUpdate(const QString &parameter, const QVariant &valueTypes, const QVariant &values);

private:
    ResourceManager(QObject* parent = nullptr);
    ~ResourceManager();

    Daqc* m_daqc;
    QReadWriteLock* m_readWriteLock;
    static bool m_initialized;
};