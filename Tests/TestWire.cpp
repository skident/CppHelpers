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



TEST(Wire, Casts)
{
    EXPECT_EQ((int)wire(123), int(123));
    EXPECT_EQ((short)wire(123 * 2), short(246));
    EXPECT_EQ((long long)wire(12345212345676542), 12345212345676542);
}


TEST(Wire, Modifications)
{
    // test substr
    EXPECT_EQ(wire(123).substr(1,1), wire("2"));
    EXPECT_EQ(wire(123).substr(1,2), wire("23"));
    
    
    // test remove
    EXPECT_EQ(wire(1234554321231).remove(4), wire("12355321231"));


    // test contatenation
    wire str;
    const int n = 10;
    str += wire(n) + "112" + 'c';
    EXPECT_EQ(string("10112c"), str);

    
    // test trim(s)
    wire test("  123   ");
    EXPECT_EQ(wire("123"), test.trim());
    EXPECT_EQ(wire("123   "), test.ltrim());
    EXPECT_EQ(wire("  123"), test.rtrim());
    
    // test working with streams
    wire str2("Work with streams str");
    stringstream ss;

    ss << str2;
    EXPECT_EQ(string("Work with streams str"), ss.str());

    
    // Test split string on chunks
    wire str3(1234512367123);
    vector<wire> splitted = {"345", "367", "3"};
    EXPECT_EQ(splitted, str3.split(12));

    
    // Test access by index
    wire charObj('c');
    EXPECT_EQ(wire('c'), charObj[0]);
    
    charObj[0] = 'd';
//    EXPECT_NE(wire('c'), charObj[0]);
//    EXPECT_EQ(wire('d'), charObj[0]);
    
    
    // Test padding, masking and multiply
    EXPECT_EQ(wire(777).padding("*", 2, 3), wire("**777***"));
    EXPECT_EQ(wire("1234567890").masking("#", 4), wire("1234##7890"));
    EXPECT_EQ( wire("1234567890").masking(wire("#").multiply(2), 4), wire("1234####7890"));
    EXPECT_EQ(wire("1234567890").masking("*", 8), wire("1234567890"));
    EXPECT_EQ(wire("123").multiply(3), wire("123123123"));
    EXPECT_EQ(wire("*").multiply(5), wire("*****"));
}



TEST(Wire, Assign)
{
    wire s = "12312";
    wire s2 = 1.3;
    wire s3 = true;
    wire s4 = 'c';
    
    EXPECT_EQ(s, wire("12312"));
    EXPECT_EQ(s2, wire("1.3"));
    EXPECT_EQ(s3, wire("true"));
    EXPECT_EQ(s4, wire("c"));
              
}


