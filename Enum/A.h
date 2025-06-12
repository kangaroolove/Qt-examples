#pragma once

namespace AZone {

class A
{
public:
    enum AEnumFirst : unsigned int { X, Y };
    enum class AEnumSecond : unsigned int { I, J };

    A();
    ~A();

private:

};
}