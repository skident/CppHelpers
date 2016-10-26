//
//  sample_wire.cpp
//  eos
//
//  Created by Skident on 10/26/16.
//
//

#include "sample_wire.hpp"


//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
/// Test code!!! Shoud be moved to its own file ///

#include <sstream>
#include <eos/io/print.hpp>
#include <iostream>
#include <string>
#include <eos/types/wire.hpp>

using namespace std;
using namespace eos;

void run_wire_samples()
{
    // test casts from string <-> String
    {
        string res = wire("Implicit cast test");
        wire res2 = res;
        cout << "string vaue: '" << res << "', String value: '" << res2 << "'" << endl;
    }
    
    // test working with streams
    {
        wire str("Work with streams str");
        stringstream ss;
        
        ss << str;
        cout << str << endl;
        cout << ss.str() << endl; // the remain part
    }
    
    
    // test trim(s)
    {
        wire test("  123   ");
        cout << test << endl;
        // trim changes the real object
        cout << "'" << wire(test).ltrim() << "'" << endl;
        cout << "'" << wire(test).rtrim() << "'" << endl;
        cout << "'" << wire(test).trim() << "'" << endl;
    }
    
    
    // test substr
    {
        wire str("123");
        cout << str.substr(1,2) << endl;
    }
    
    // test remove and removeAll
    {
        wire digits(1234554321231);
        digits.remove(4);
        cout << "digits after remove 4: " << digits << endl;
        
        digits.removeAll(23);
        cout << "digits after remove all 23: " << digits << endl;
        
        wire word("abcabab");
        cout << word.removeAll("ab") << endl;
    }
    
    
    // Test split string on chunks
    {
        wire str(1234512367123);
        cout << str.split(12) << endl;
    }
    
    
    // Test constructor with char
    {
        wire charObj('c');
        cout << charObj << endl;
    }
    
    // Test contains method
    {
        wire res(33344511);
        cout << "Does contain digit 3? " << res.contains(3) << endl;
        cout << "Does contain digit 0? " << res.contains(0) << endl;
    }
    
    // implicit casts
    {
        int digit = wire(123);
        short shortDigit = wire(321);
        const long long bigData = wire(12345212345676543);
        const char symbol = wire("qwerty");
        char symbol2 = wire();
        
        cout << digit << endl;
        cout << shortDigit << endl;
        cout << bigData << endl;
        cout << symbol << endl;
        cout << "'" << symbol2 << "'" << endl;
    }
    
    // concatenate test
    {
        wire str, str2, str3;
        const int n = 10;
        
        str3 += wire(n) + "112" + 'c';
        
        for (int i = 0 ; i < 10; i++)
        {
            str = str + i;
            str2 += i;
        }
        
        
        
        cout << str << endl;
        cout << str2 << endl;
        cout << str3 << endl;
    }
    
    
    // Tests with iterators
    {
        wire str("qwerty");
        for (const auto& symbol : str)
            cout << symbol << " : ";
        cout << endl;
    }
    
}
