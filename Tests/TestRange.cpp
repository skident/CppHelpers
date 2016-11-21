//
//  TestRange.cpp
//  eos_tests
//
//  Created by Skident on 11/18/16.
//
//

#include <iostream>

#include <gtest/gtest.h>
#include <eos/types/range.hpp>


using namespace std;
using namespace eos;


TEST(Range, Basic)
{
    eos::range<int> rangeInt;
    eos::range<int> rangeInt2;

    EXPECT_EQ(rangeInt, rangeInt2);
    EXPECT_EQ(rangeInt.empty(), true);
    
    
    rangeInt.insert({1, 3});
    EXPECT_NE(rangeInt, rangeInt2);
    EXPECT_EQ(rangeInt.empty(), false);
    EXPECT_EQ(false, rangeInt.find(0));
    EXPECT_EQ(true, rangeInt.find(1));
    EXPECT_EQ(true, rangeInt.find(2));
    EXPECT_EQ(false, rangeInt.find(3));
    
    
    rangeInt.insert({1, 7});
    EXPECT_EQ(true, rangeInt.find(6));
    EXPECT_EQ(false, rangeInt.find(7));
    
    
    rangeInt.insert({8, 11});
    EXPECT_EQ(true, rangeInt.find(8));
    EXPECT_EQ(true, rangeInt.find(10));
    EXPECT_EQ(false, rangeInt.find(11));
    
    
    rangeInt2.insert({1, 3});
    rangeInt2.insert({1, 7});
    EXPECT_NE(rangeInt2, rangeInt);
    
    
    rangeInt2.insert({8, 11});
    EXPECT_EQ(rangeInt2, rangeInt);
    
    
    rangeInt.clear();
    EXPECT_EQ(true, rangeInt.empty());
    EXPECT_NE(rangeInt2, rangeInt);

    
    rangeInt2.clear();
    EXPECT_EQ(true, rangeInt2.empty());
    EXPECT_EQ(rangeInt2, rangeInt);
}
