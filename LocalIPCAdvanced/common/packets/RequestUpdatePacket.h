#pragma once

#include "RequestPacket.h"

class RequestUpdatePacket : public RequestPacket
{
public:
    RequestUpdatePacket(const QString& parameter, const QVariant& values, const QVariant& valueTypes);
    RequestUpdatePacket(const RequestUpdatePacket& packet);
    ~RequestUpdatePacket();

    static RequestUpdatePacket fromJson(const QJsonObject& object);
protected:
    QJsonObject generateData() override;
};