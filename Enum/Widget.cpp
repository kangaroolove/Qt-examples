#include "Widget.h"

#include <QDebug>

#include "A.h"
#include "B.h"

using A = AZone::A;
using B = BZone::B;

Widget::Widget(QWidget *parent) : QWidget(parent) {
    A a;
    B b;

    b.getTextFromAEnumFirst(A::X);

    b.getTextFromAEnumSecond(A::AEnumSecond::I);
}