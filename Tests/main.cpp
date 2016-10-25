#include <iostream>

#include <eos/types/wire.hpp>
#include <gtest/gtest.h>

using namespace std;


int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();
	return ret;
}

TEST(ValidatorRegex, ManualPositive)
{
	//EXPECT_EQ(true, 1, 1);
}