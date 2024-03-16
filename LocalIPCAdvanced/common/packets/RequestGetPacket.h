#pragma once

#include "Packet.h"

class RequestGetPacket : public Packet
{
public:
    RequestGetPacket(const QString& parameter);
    ~RequestGetPacket();

    QString getParameter() const;
protected:
    QJsonObject generateData() override;
private:
    QString m_parameter;
};