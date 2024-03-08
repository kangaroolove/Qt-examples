#pragma once

#include "ReplyPacket.h"

class ReplyGetTest : public ReplyPacket
{
public:
    ReplyGetTest(const QString& clientMessageId);
    ~ReplyGetTest();
    QJsonObject generateData() override;
};