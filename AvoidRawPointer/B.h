#pragma once

#include "A.h"

class B : public A {
public:
    B();
    ~B();

    void printf() override;

private:
};