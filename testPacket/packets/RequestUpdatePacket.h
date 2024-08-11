#pragma once

#include "Packet.h"
#include <QVariant>

class RequestUpdatePacket : public Packet
{
public:
    RequestUpdatePacket(const QString& parameter, const QVariant& values, const QVariant& valueTypes);
    RequestUpdatePacket(const RequestUpdatePacket& packet);
    static RequestUpdatePacket fromBinaryData(const QByteArray& data);
protected:
    QJsonObject generateData() override;
private:

    QString m_parameter;
    QVariant m_valueTypes;
    QVariant m_values;
};