#pragma once

#include <QString>

#include "A.h"

// namespace AZone {
// class A;
// }

// using A = AZone::A;
// using AType = A::AType;
// enum class AType : unsigned int;

namespace BZone {
class B {
public:
    B();
    ~B();
    void getTextFromAType(AZone::A::AType type);

private:
};
}  // namespace BZone