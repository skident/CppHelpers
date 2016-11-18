#include <iostream>

#include <eos/types/wire.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace eos;

GTEST_API_ int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
