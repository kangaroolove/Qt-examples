#pragma once

#include "ReplyPacket.h"

class ReplyGetPacket : public ReplyPacket
{
public:
    ReplyGetPacket(const QString& requestType, const QString& parameter, const QString& clientMessageId);
    ~ReplyGetPacket();
    QJsonObject generateData();
    virtual QVariant getValue() = 0;
    virtual QString getValueType() = 0;
private:
    QString m_requestType;
    QString m_parameter;
};