#pragma once

#include "Packet.h"
#include <QVariant>

class RequestUpdatePacket : public Packet
{
public:
    RequestUpdatePacket(const QString& parameter, const QVariant& values, const QVariant& valueTypes);
    RequestUpdatePacket(const RequestUpdatePacket& packet);
    ~RequestUpdatePacket();

    QString getParameter() const;
    QVariant getValueTypes() const;
    QVariant getValues() const;
    static RequestUpdatePacket fromJson(const QJsonObject& object);
protected:
    QJsonObject generateData() override;
private:
    QString m_parameter;
    QVariant m_values;
    QVariant m_valueTypes;
};