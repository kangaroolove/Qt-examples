#pragma once

#include <QByteArray>

class Packet
{
public:
    Packet();
    ~Packet();
    virtual QByteArray toJson() = 0;
private:

};