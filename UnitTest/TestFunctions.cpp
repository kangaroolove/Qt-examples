#include "TestFunctions.h"
#include "Functions.h"

QTEST_MAIN(TestFunctions)

TestFunctions::TestFunctions() {}

TestFunctions::~TestFunctions() {}

void TestFunctions::testSumError() {
    // error
    QCOMPARE(Functions::sum(1, 1), -3);
    QCOMPARE(Functions::sum(-10, 5), 0);
}

void TestFunctions::testSum() {
    QCOMPARE(Functions::sum(0, 0), 0);
    QCOMPARE(Functions::sum(3, 5), 8);
    QCOMPARE(Functions::sum(-5, -10), -15);
    QCOMPARE(Functions::sum(-10, 5), -5);
}
