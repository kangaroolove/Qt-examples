#pragma once

#include "ReplyPacket.h"

class ReplyGetTest : public ReplyPacket
{
public:
    ReplyGetTest();
    ~ReplyGetTest();
    QJsonObject generateData() override;
};