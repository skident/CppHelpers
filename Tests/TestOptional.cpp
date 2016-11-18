//
//  TestOptional.cpp
//  eos_tests
//
//  Created by Skident on 11/11/16.
//
//

#include <iostream>

#include <gtest/gtest.h>
#include <eos/types/optional.hpp>


using namespace std;
using namespace eos;


TEST(Optional, Basic)
{
    optional<int> optInt;
    
    EXPECT_EQ(optInt, nullptr);
    EXPECT_EQ(!optInt, true);
    
    optInt.store(33);
    EXPECT_EQ(!optInt, false);
    EXPECT_EQ(optInt, 33);
    
    EXPECT_NE(optInt, 25);
    
    optInt.reset();
    EXPECT_EQ(optInt, nullptr);
    EXPECT_EQ(!optInt, true);
    EXPECT_NE(optInt, 25);
    
    optional<string> optStr("qwerty");
    string extracted = optStr;
    
    EXPECT_EQ(optStr, "qwerty");
    EXPECT_EQ(extracted, "qwerty");
    
    optional<string> optStr2("qwe");
    EXPECT_NE(extracted, optStr2);

    optStr2.store("qwerty");
    EXPECT_EQ(extracted, optStr2);
}
