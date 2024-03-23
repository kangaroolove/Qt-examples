#pragma once

#include "RequestPacket.h"
class RequestGetPacket : public RequestPacket
{
public:
    RequestGetPacket(const QString& parameter, const QVariant& values = QVariant(), const QVariant& valueTypes = QVariant(), const QString& messageId = QString());
    RequestGetPacket(const RequestGetPacket& packet);
    ~RequestGetPacket();

    static RequestGetPacket fromJson(const QJsonObject& object);
protected:
    QJsonObject generateData() override;
};