#include "B.h"

#include <QDebug>

namespace BZone {

B::B()
{

}

B::~B()
{

}

void B::getTextFromAType(AZone::A::AType type) {
    if (type == AZone::A::X) {
        qDebug() << "A";
    }
}

}  // namespace BZone
