/*
   Sample Code For gtest
*/

#include "gtest/gtest.h"
//#include "calculator.h"

/*
Fatal assertion	Nonfatal assertion	Verifies
ASSERT_TRUE(condition);	EXPECT_TRUE(condition);	condition is true
ASSERT_FALSE(condition);	EXPECT_FALSE(condition);	condition is false
*/
/*
Fatal assertion	Nonfatal assertion	Verifies
ASSERT_EQ(expected, actual);	EXPECT_EQ(expected, actual);	expected == actual
ASSERT_NE(val1, val2);	EXPECT_NE(val1, val2);	val1 != val2
ASSERT_LT(val1, val2);	EXPECT_LT(val1, val2);	val1 < val2
ASSERT_LE(val1, val2);	EXPECT_LE(val1, val2);	val1 <= val2
ASSERT_GT(val1, val2);	EXPECT_GT(val1, val2);	val1 > val2
ASSERT_GE(val1, val2);	EXPECT_GE(val1, val2);	val1 >= val2
*/
/*
Fatal assertion	Nonfatal assertion	Verifies
ASSERT_STREQ(expected_str,actual_str);	EXPECT_STREQ(expected_str,actual_str);	the two C strings have the same content
ASSERT_STRNE(str1, str2);	EXPECT_STRNE(str1, str2);	the two C strings have different content
ASSERT_STRCASEEQ(expected_str,actual_str);	EXPECT_STRCASEEQ(expected_str,actual_str);	the two C strings have the same content, ignoring case
ASSERT_STRCASENE(str1, str2);	EXPECT_STRCASENE(str1, str2);	the two C strings have different content, ignoring case
*/


class calculator_test : public testing::Test
{

public:
	int sum(int a, int b)
	{
		return a + b;
	}

	int minus(int a, int b)
	{
		return a - b;
	}
};

TEST_F(calculator_test, sum)
{
	EXPECT_EQ(2, sum(1,1));
}

TEST_F(calculator_test, minus)
{
	EXPECT_EQ(1, minus(2,1));
}