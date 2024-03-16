#pragma once

#include "Packet.h"
class RequestGetPacket : public Packet
{
public:
    RequestGetPacket(const QString& parameter);
    RequestGetPacket(const RequestGetPacket& packet);
    ~RequestGetPacket();

    QString getParameter() const;
    static RequestGetPacket fromJson(const QJsonObject& object);
protected:
    QJsonObject generateData() override;
private:
    QString m_parameter;
};