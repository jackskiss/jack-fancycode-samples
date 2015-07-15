/**
	calculator sample code
**/

#include "gtest/gtest.h"

class calculator_test : public ::testing::test
{
public:
	int sum(int a, int b);
	int minus(int a, int b);
};