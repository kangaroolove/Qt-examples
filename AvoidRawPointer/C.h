#pragma once

#include "A.h"

class C : public A {
public:
  C();
  ~C();

  void printf() override;

private:
};