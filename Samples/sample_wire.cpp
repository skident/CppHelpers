//
//  sample_wire.cpp
//  eos
//
//  Created by Skident on 10/26/16.
//
//

#include "samples.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>


#include <eos/types/wire.hpp>
#include <eos/io/print.hpp>

using namespace std;
using namespace eos;

void sample_implicit_casts()
{
    cout << endl;
    cout << "=========================================" << endl;
    cout << "           Implicit casts samples        " << endl;
    cout << "=========================================" << endl;

    
    // test casts from std::string <-> eos::wire
    {
        string res = wire("Implicit cast test");
        wire res2 = res;    // case from std::string to wire
        cout << "std::string vaue: '" << res << "', eos::wire value: '" << res2 << "'" << endl;
    }
    
    // implicit casts
    {
        int digit = wire(123);                              // digit == 123
        short shortDigit = wire(321*2);                     // shortDigit == 642
        const long long bigData = wire(12345212345676542);  // bigData == 12345212345676542
        const char symbol = wire("qwerty");                 // symbol == 'q'
        char symbol2 = wire();                              // symbol2 == ' '
        
        dump(digit);
        dump(shortDigit);
        dump(bigData);
        dump(symbol);
        cout << "'" << symbol2 << "'" << endl;  // quotes for show the space
    }
}


void sample_algorithms_usage()
{
    cout << endl;
    cout << "=========================================" << endl;
    cout << "          std::algorithms usage          " << endl;
    cout << "=========================================" << endl;

    {
        wire str("pvdqsx");
        cout << "Value: " << str << endl;
        
        for (auto& symbol : str)
        {
            symbol++;
        }
        
        cout << "Changed value: ";
        for (const auto& symbol : str)
        {
            cout << symbol << " : ";
        }
        cout << endl;
        
        cout << "Reversed: " << str.reverse() << endl;
        
        string s;
        transform(str.begin(), str.end(), back_inserter(s), (int (*)(int))toupper);
        cout << "Upper Case: " << s << endl;

    }
}

void sample_of_modifications()
{
    cout << endl;
    cout << "=========================================" << endl;
    cout << "          eos::wire modifications        " << endl;
    cout << "=========================================" << endl;
    
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
        
        dump(str);
        dump(str2);
        dump(str3);
    }
    
    // test trim(s)
    {
        wire test("  123   ");
        dump(test);
        // trim changes the real object
        cout << "ltrim '" << wire(test).ltrim() << "'" << endl;
        cout << "rtrim '" << wire(test).rtrim() << "'" << endl;
        cout << "trim '" << wire(test).trim() << "'" << endl;
    }
    
    // test working with streams
    {
        wire str("Work with streams str");
        stringstream ss;
        
        ss << str;
        cout << str << endl;
        cout << ss.str() << endl; // the remain part
    }
    
    
    // Test split string on chunks
    {
        wire str(1234512367123);
        cout << str.split(12) << endl;
        cout << str.split() << endl;
    }
    
    
    // Test constructor with char
    {
        wire charObj('c');
        dump(charObj);
        dump(charObj[0]);
        charObj[0] = 'd';
    }
    
    // Test contains method
    {
        wire res(33344511);
        dump(res);
        cout << "Does contain digit 3? " << res.contains(3) << endl;
        cout << "Does contain digit 0? " << res.contains(0) << endl;
    }
}


//#define PRINT(value) cout << #value << " " << value << endl;
void sample_padding()
{
    cout << endl;
    cout << "=========================================" << endl;
    cout << " eos::wire padding, masking, multiplying " << endl;
    cout << "=========================================" << endl;

    wire paddedData = wire(777).padding("*", 2, 3);
    wire secretInfo = wire("1234567890").masking("#", 4);
    wire secretInfo2 = wire("1234567890").masking(wire("#").multiply(2), 4);
    wire secretInfo3 = wire("1234567890").masking("*", 8);
    wire multiplied = wire("123").multiply(3);
    wire multiplied2 = wire("*").multiply(5);
        
    dump(paddedData);   // **777***
    dump(secretInfo);   // 1234##7890
    dump(secretInfo2);  // 1234####7890
    dump(secretInfo3);  // 1234567890
    dump(multiplied);   // 123123123
    dump(multiplied2);  // *****
}

void sample_stream()
{
    cout << endl;
    cout << "=========================================" << endl;
    cout << " eos::wire using as stream " << endl;
    cout << "=========================================" << endl;

	wire streamWire;
	
	streamWire << 11 << " years";
	dump(streamWire);
}


void sample_assign()
{
	cout << endl;
	cout << "=========================================" << endl;
	cout << " eos::wire assignment operator " << endl;
	cout << "=========================================" << endl;

	wire s = "12312";
	wire s2 = 1.3;
	wire s3 = true;
	wire s4 = 'c';

	dump(s);
	dump(s2);
	dump(s3);
	dump(s4);
}

void run_wire_samples()
{
    sample_implicit_casts();
    sample_algorithms_usage();
    sample_of_modifications();
    
    sample_padding();
	sample_stream();
	sample_assign();
}
