#include "B.h"

#include <QDebug>

namespace BZone {

B::B()
{

}

B::~B()
{

}

void B::getTextFromAEnumFirst(A::AEnumFirst type) {
    if (type == A::X) {
        qDebug() << "A";
    }
}

void B::getTextFromAEnumSecond(A::AEnumSecond type) {
    if (type == A::AEnumSecond::I) {
        qDebug() << "I";
    }
}
}  // namespace BZone
