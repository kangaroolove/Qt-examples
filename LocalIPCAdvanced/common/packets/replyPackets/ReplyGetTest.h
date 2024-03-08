#pragma once

#include "ReplyPacket.h"

class ReplyGetTest : public ReplyPacket
{
public:
    ReplyGetTest(const QString& clientMessageId);
    ~ReplyGetTest();
    QVariant getValue() override;
    QString getValueType() override;
};