#pragma once

#include "Packet.h"
#include <QVariant>

class RequestPacket : public Packet
{
public:
    RequestPacket();
    RequestPacket(const QString& parameter, const QVariant& values, const QVariant& valueTypes);
    ~RequestPacket();

    QString getParameter() const;
    QVariant getValueTypes() const;
    QVariant getValues() const;
protected:
    QString m_parameter;
    QVariant m_values;
    QVariant m_valueTypes;
};