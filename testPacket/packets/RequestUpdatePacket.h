#pragma once

#include "Packet.h"
#include <QVariant>

class RequestUpdatePacket : public Packet
{
public:
    RequestUpdatePacket(const QString& parameter, const QVariant& values, const QStringList& valueTypes);
    RequestUpdatePacket(const RequestUpdatePacket& packet);
    static RequestUpdatePacket fromJson(const QByteArray& data);
    QString getParameter() const;
    QStringList getValueTypes() const;
    QVariant getValues() const;
    void printfSelf() override;

    static const QString PARAMETER;
    static const QString VALUE_TYPES;
    static const QString VALUES;
protected:
    QJsonObject generateData() override;
private:
    QString m_parameter;
    QStringList m_valueTypes;
    QVariant m_values;
};