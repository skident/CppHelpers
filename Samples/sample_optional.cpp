//
//  sample_optional.cpp
//  eos
//
//  Created by Skident on 11/11/16.
//
//

#include <iostream>

#include "eos/types/optional.hpp"

using namespace eos;
using namespace std;

void test_optional_simple()
{
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

    
}
