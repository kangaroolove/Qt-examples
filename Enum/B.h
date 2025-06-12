#pragma once

#include <QString>

#include "A.h"

using A = AZone::A;
// using AType = A::AType;
// enum class AType : unsigned int;

namespace BZone {
class B {
public:
    B();
    ~B();
    void getTextFromAEnumFirst(A::AEnumFirst type);
    void getTextFromAEnumSecond(A::AEnumSecond type);

private:
};
}  // namespace BZone