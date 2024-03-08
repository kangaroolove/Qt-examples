#pragma once

#include "RequestPacket.h"

class RequestGetTest : public RequestPacket
{
public:
    RequestGetTest();
    ~RequestGetTest();
    QJsonObject generateData() override;
};