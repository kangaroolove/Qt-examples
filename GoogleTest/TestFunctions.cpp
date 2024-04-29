#include "TestFunctions.h"
#include "Functions.h"

TestFunctions::TestFunctions()
{

}

TestFunctions::~TestFunctions()
{

}

TEST(TestFunction, BasicOperation) 
{
    EXPECT_EQ(Functions::sum(0, 0), 0);
    EXPECT_EQ(Functions::sum(3, 5), 8);
    EXPECT_EQ(Functions::sum(-5, -10), -15);
    EXPECT_EQ(Functions::sum(-10, 5), -5);
}

TEST(TestFunction, errorOperation) 
{
    EXPECT_EQ(Functions::sum(5, 5), 10);
    EXPECT_EQ(Functions::sum(-10, 5), 0);
}

