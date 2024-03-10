#pragma once

#include <QRunnable>
#include <QString>
#include <QVariant>

class UpdateValueInfo
{
public:
    QString parameter;
    QString valueType;
    QVariant value;
};

class UpdateValueTask : public QRunnable
{
public:
    UpdateValueTask(const UpdateValueInfo& updateValueInfo);
    ~UpdateValueTask();
    void run() override;
private:
    UpdateValueInfo m_updateValueInfo;
};