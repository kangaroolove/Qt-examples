#pragma once

#include "RequestPacket.h"
#include <QVariant>

class RequestUpdatePacket : public RequestPacket
{
public:
    RequestUpdatePacket(const QString& parameter, const QVariant& value, const QString& valueType);
    ~RequestUpdatePacket();
    QJsonObject generateData() override;
private:
    QString m_parameter;
    QVariant m_value;
    QString m_valueType;
};