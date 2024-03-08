#pragma once

#include "RequestPacket.h"

class RequestGetPacket : public RequestPacket
{
public:
    RequestGetPacket(const QString& parameter);
    ~RequestGetPacket();
    QJsonObject generateData() override;
private:
    QString m_parameter;
};