#include "Widget.h"
#include "B.h"
#include "C.h"
#include <QDebug>
#include <memory>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    std::unique_ptr<A> b = std::make_unique<B>();
    std::unique_ptr<A> c = std::make_unique<C>();

    printf(*b);
    printf(*c);
}

void Widget::printf(A &a) { a.printf(); }
