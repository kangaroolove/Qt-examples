#pragma once

#include "Packet.h"
#include <QJsonObject>
#include <QString>
class ReplyPacket : public Packet
{
public:
    ReplyPacket(const QString& parameter, const QString& requestType, const QString& clientMessageId);
    ~ReplyPacket();
    QByteArray toJson() override;
protected:
    virtual QVariant getValue() = 0;
    virtual QString getValueType() = 0;
    QJsonObject generateData() override;

    QString m_parameter;
    QString m_requestType;
    QString m_clientMessageId;
};