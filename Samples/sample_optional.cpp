//
//  sample_optional.cpp
//  eos
//
//  Created by Skident on 11/11/16.
//
//

#include <iostream>

#include "samples.hpp"
#include "eos/types/optional.hpp"
#include <string>

#include "eos/types/field.hpp"

using namespace eos;
using namespace std;

void test_optional_simple()
{
    cout << endl;
    cout << "=========================================" << endl;
    cout << "Sample of eos::optional" << endl;
    cout << "=========================================" << endl;

    
    optional<int> optInt;
    if (!optInt)
        cout << "Empty" << endl;
    
    optInt.store(33);
    if (optInt == nullptr)
        cout << "Empty again" << endl;
    
    if (optInt == 33)
        cout << "Equal" << endl;
    
    if (optInt != 25)
        cout << "Not 25" << endl;
    
    optInt.reset();
    if (!optInt)
        cout << "Empty" << endl;
    
    if (optInt != 27)
        cout << "Not 27" << endl;

    
    optional<string> optStr("qwerty");
    string extracted = optStr;
    cout << optStr << endl;
    
    optional<string> optStr2("qwe");
    
    if (optStr != optStr2)
        cout << "Two optionals are not equal" << endl;
    
    optStr2.store("qwerty");
    
    if (optStr == optStr2)
        cout << "Two optionals are equal" << endl;
}


void test_limitation()
{
    field<int> trnId;
    
    // only digits 3 and 4
    trnId.setValueLimits(1, 10)     // 1 .. 10
         .setLengthLimits(1, 2)     // -9 .. 99
         .setValidator([](const int& value){ return (value % 4 == 0); }); // -8, -4, 0, 4, 8
    
    try
    {
        trnId.validate(8);
    } catch (std::runtime_error& ex)
    {
        cout << ex.what() << endl;
    }
}


void run_optional_samples()
{
    test_limitation();
    test_optional_simple();
}
