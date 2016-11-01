#include <iostream>

#include <eos/types/wire.hpp>
#include "CppUnitLite/TestHarness.h"

using namespace std;

SimpleString StringFrom(const std::string& value)
{
	return SimpleString(value.c_str());
}


int main()
{
	TestResult tr;
	TestRegistry::runAllTests(tr);

	return 0;
}


TEST(Stack, creation)
{
	/*std::string s;
	LONGS_EQUAL(0, s.size());
	std::string b = "asa";
	CHECK_EQUAL(string("asa"), b);*/
}


//TEST(ValidatorRegex, ManualPositive)
//{
//	//EXPECT_EQ(true, 1, 1);
//}