//
//  TestWire.cpp
//  eos_tests
//
//  Created by Skident on 11/4/16.
//
//

#include <iostream>
#include <vector>

#include <eos/types/wire.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace eos;


TEST(Wire, Positive)
{
    EXPECT_EQ(static_cast<int>(wire(123456)), 123456);
    EXPECT_EQ(wire(), wire());
    EXPECT_EQ(wire(123).reverse(), wire(321));
    EXPECT_EQ(wire("abc").padding("_", 3), wire("___abc___"));
    EXPECT_EQ(wire("a;b;c;d").split(";"), vector<wire>({"a", "b", "c", "d"}));
    
    EXPECT_EQ(wire("fork")
              .masking("*", 1, 2)
              .masking("%", 2, 1).str(), "f*%k");
    
    
    EXPECT_EQ(wire("omen") + 666, wire("omen666"));
    
    EXPECT_EQ(wire("clown"), join(vector<char>({'c', 'l', 'o', 'w', 'n'})));
    EXPECT_EQ(wire("c.l.o.w.n"), join(vector<char>({'c', 'l', 'o', 'w', 'n'}), wire(".")));
              
}
