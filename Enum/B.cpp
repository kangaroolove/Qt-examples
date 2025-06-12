#include "B.h"

#include <QDebug>

namespace BZone {

B::B()
{

}

B::~B()
{

}

void B::getTextFromAType(A::AType type) {
    if (type == A::X) {
        qDebug() << "A";
    }
}

}  // namespace BZone
