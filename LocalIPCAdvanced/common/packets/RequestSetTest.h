#pragma once

#include "RequestPacket.h"

class RequestSetTest : public RequestPacket
{
public:
    RequestSetTest();
    ~RequestSetTest();
    QJsonObject generateData() override;
};