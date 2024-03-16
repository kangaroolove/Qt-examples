#pragma once

#include "Packet.h"
#include <QVariant>

class RequestUpdatePacket : public Packet
{
public:
    RequestUpdatePacket(const QString& parameter, const QVariant& value, const QString& valueType);
    RequestUpdatePacket(const RequestUpdatePacket& packet);
    ~RequestUpdatePacket();

    QString getParameter() const;
    QString getValueType() const;
    QVariant getValue() const;
    static RequestUpdatePacket fromJson(const QJsonObject& object);
protected:
    QJsonObject generateData() override;
private:
    QString m_parameter;
    QVariant m_value;
    QString m_valueType;
};