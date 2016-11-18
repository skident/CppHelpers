#include "samples.hpp"

#include <iostream>

#include "eos/io/print.hpp"
#include <map>
#include <set>
#include <string>
#include <vector>
#include <list>
#include <queue>

#ifdef MODERN_CPP_AVAILABLE
    #include <unordered_set>
    #include <unordered_map>
    #include <array>
    #include <forward_list>
#endif


using namespace eos;
using namespace std;


void sample_stl_helpers_C11()
{
#ifdef MODERN_CPP_AVAILABLE
	cout << endl;
    cout << "=========================================" << endl;
    cout << "Sample of stl_helpers for C++11 and greater" << endl;
    cout << "=========================================" << endl;

    // 1. Sample std::array
    std::array<int,6> myarray;
    myarray.fill(5);
	cout << "Array: " << myarray << endl;
    print(myarray);

    // 2. Sample forward_list
    forward_list<int> second = {20, 40, 80};
    cout << "Forward list: " << second << endl;
    print(second);

    // 3. Sample unordered_set
    unordered_set<int> usetInt = {8,6,5,4,3,2};
	cout << "Unordered Set: " << usetInt << endl;
    print(usetInt);

    // 4. Sample unordered_map
    unordered_map<int, string> umapIntStr = {{11, "qss"}, {22, "wss"}, {33, "zss"}};
	cout << "Unordered Map: " << umapIntStr << endl;
    print(umapIntStr);

#endif
}

void sample_stl_helpers_C03()
{
	cout << endl;
    cout << "=========================================" << endl;
    cout << " Sample of stl_helpers for C++98 and C++03 " << endl;
    cout << "=========================================" << endl;

    // 1. Sample vector
    vector<string> vecStr;
    vecStr.push_back("111");
    vecStr.push_back("221");
    vecStr.push_back("11341");
	cout << "Vector: " << vecStr << endl;
    print(vecStr);

    // 2. Sample list
    list<int> listInt;
    listInt.push_back(1);
    listInt.push_back(95);
    listInt.push_back(33);
	cout << "List: " << listInt << endl;
    print(listInt);

    // 3. Sample set
    set<int> setInt;
    setInt.insert(4);
    setInt.insert(5);
	cout << "Set: " << setInt << endl;
    print(setInt);

    // 4. Sample map
    map<int, string> mapIntStr;
    mapIntStr[11] = "ssss";
    mapIntStr[911] = "sx";
    mapIntStr[124] = "sssefrg";
    mapIntStr[01] = "45448";
    mapIntStr[19] = "3434t";
	cout << "Map: " << mapIntStr << endl;
    print(mapIntStr);

    // 5. Sample deque
    std::deque<int> mydeque;
    for (int i = 1; i<6; i++) 
    	mydeque.push_back(i*2); // 2 4 6 8 10
	cout << "deque: " << mydeque << endl;
    print(mydeque);
}


class Info
{
private:
    string name;
    int age;

public:
    Info(string name, int age)
        : name(name)
        , age(age)
    {

    }

    friend ostream& operator<<(ostream& os, const Info& info);
};

ostream& operator<<(ostream& os, const Info& info)
{
    os << "Name: " << info.name << " age: " << info.age;
    return os;
}

void sample_stl_helpers_C03_own_type()
{
	cout << endl;
    cout << "=========================================" << endl;
    cout << "     Sample of stl_helpers on own class    " << endl;
    cout << "=========================================" << endl;

    vector<Info> vecStr;
    vecStr.push_back(Info("Biba", 22));
    vecStr.push_back(Info("Boba", 21));
    print(vecStr);
}

void sample_trim()
{
	cout << endl;
	cout << "=========================================" << endl;
	cout << "        Sample of trimming the string      " << endl;
	cout << "=========================================" << endl;

    // ltrim
    cout << "========================" << endl;
    cout << "left trim Sample" << endl;
    cout << "========================" << endl;
    cout << "Sample #1 " << "'" << ltrim("") << "'" << endl;
    cout << "Sample #2 " << "'" << ltrim("12345") << "'" << endl;
    cout << "Sample #3 " << "'" << ltrim("   12345   ") << "'" << endl;
    cout << "Sample #4 " << "'" << ltrim("           ") << "'" << endl;
    cout << "Sample #5 " << "'" << ltrim("          1") << "'" << endl;
    cout << "Sample #6 " << "'" << ltrim("1         1") << "'" << endl;

    // rtrim
    cout << "========================" << endl;
    cout << "rtrim Sample" << endl;
    cout << "========================" << endl;
    cout << "Sample #1 " << "'" << rtrim("") << "'" << endl;
    cout << "Sample #2 " << "'" << rtrim("12345") << "'" << endl;
    cout << "Sample #3 " << "'" << rtrim("   12345   ") << "'" << endl;
    cout << "Sample #4 " << "'" << rtrim("           ") << "'" << endl;
    cout << "Sample #5 " << "'" << rtrim("1          ") << "'" << endl;
    cout << "Sample #6 " << "'" << rtrim("1         1") << "'" << endl;

    // trim
    cout << "========================" << endl;
    cout << "trim Sample" << endl;
    cout << "========================" << endl;
    cout << "Sample #1 " << "'" << trim("") << "'" << endl;
    cout << "Sample #2 " << "'" << trim("12345") << "'" << endl;
    cout << "Sample #3 " << "'" << trim("   12345   ") << "'" << endl;
    cout << "Sample #4 " << "'" << trim("           ") << "'" << endl;
    cout << "Sample #5 " << "'" << trim("          1") << "'" << endl;
    cout << "Sample #6 " << "'" << trim("1          ") << "'" << endl;
    cout << "Sample #7 " << "'" << trim("1         1") << "'" << endl;
}

void sample_dump()
{
    cout << endl;
    cout << "=========================================" << endl;
    cout << "        Sample of dumping any value      " << endl;
    cout << "=========================================" << endl;
    

    vector<int> v={1,2,3,4,5};
    dump(v);
    string result = "some info";
    dump(result);
    dump("result");
}

void run_output_samples()
{
    sample_stl_helpers_C03();
    sample_stl_helpers_C11();
    sample_stl_helpers_C03_own_type();
    sample_trim();
    sample_dump();
}

