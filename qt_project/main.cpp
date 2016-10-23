#include <iostream>

#include "print.hpp"
#include <map>
#include <set>
#include <array>
#include <string>
#include <vector>
#include <string>
#include <list>
#include <vector>
#include <set>
#include <queue>

#ifdef MODERN_CPP_AVAILABLE
    #include <unordered_set>
    #include <unordered_map>
    #include <array>
    #include <forward_list>
#endif


using namespace eos;
using namespace std;

void simple()
{
    multimap<string, string> myMap = {{"1", "2"}, {"3", "4"}};
    eos::print(myMap);

    multiset<int> mySet = {1, 3, 1, 3, 2, 3};
    eos::print(mySet);
    cout << mySet << "asass" << endl;

    map<string, string> myMap2 = {{"1", "2"}, {"3", "4"}};
    cout << "ss" << myMap2 << endl;
    cout << "asdas" << myMap << endl;

    array<int, 10> myArray = {1, 2, 3, 4, 5, 6};
    cout << "ada " << myArray << endl;

    vector<int> myVec = {2,3,4,5};
    cout << "My vector: " << myVec << endl;


    set<int> mySet2 = {1,2,3,4};
    cout << "ass" << 11 << mySet2 << endl;
    print(mySet2);

}




void test_stl_helpers_C11()
{
#ifdef MODERN_CPP_AVAILABLE
    cout << "=========================================" << endl;
    cout << "Test of stl_helpers for C++11 and greater" << endl;
    cout << "=========================================" << endl;

    // 1. Test std::array
    std::array<int,6> myarray;
    myarray.fill(5);
    cout << "Array: " << myarray;
    print(myarray);

    // 2. Test forward_list
    forward_list<int> second = {20, 40, 80};
    cout << "forward_list: " << second;
    print(second);


    // 5. Test unordered_set
    unordered_set<int> usetInt = {8,6,5,4,3,2};
    cout << "Unordered Set: " << usetInt;
    print(usetInt);



    // 6. Test unordered_map
    unordered_map<int, string> umapIntStr = {{11, "qss"}, {22, "wss"}, {33, "zss"}};
    cout << "Unordered Map: " << umapIntStr;
    print(umapIntStr);

#endif
}

void test_stl_helpers_C03()
{
    cout << "=========================================" << endl;
    cout << " Test of stl_helpers for C++98 and C++03 " << endl;
    cout << "=========================================" << endl;

    // 1. Test vector
    vector<string> vecStr;
    vecStr.push_back("111");
    vecStr.push_back("221");
    vecStr.push_back("11341");
    cout << "Vector: " << vecStr;
    print(vecStr);

    // 2. Test list
    list<int> listInt;
    listInt.push_back(1);
    listInt.push_back(95);
    listInt.push_back(33);
    cout << "List: " << listInt;
    print(listInt);

    // 3. Test set
    set<int> setInt;
    setInt.insert(4);
    setInt.insert(5);
    cout << "Set: " << setInt;
    print(setInt);

    // 4. Test map
    map<int, string> mapIntStr;
    mapIntStr[11] = "ssss";
    mapIntStr[911] = "sx";
    mapIntStr[124] = "sssefrg";
    mapIntStr[01] = "45448";
    mapIntStr[19] = "3434t";
    cout << "Map: " << mapIntStr;
    print(mapIntStr);

    // 5. Test deque
    std::deque<int> mydeque;
    for (int i=1; i<6; i++) mydeque.push_back(i*2); // 2 4 6 8 10
    cout << "deque: " << mydeque;
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

void test_stl_helpers_C03_own_type()
{
    cout << "=========================================" << endl;
    cout << "     Test of stl_helpers on own class    " << endl;
    cout << "=========================================" << endl;

    vector<Info> vecStr;
    vecStr.push_back(Info("Biba", 22));
    vecStr.push_back(Info("Boba", 21));
    print(vecStr);
}

void test_trim()
{
    // ltrim
    cout << "========================" << endl;
    cout << "ltrim test" << endl;
    cout << "========================" << endl;
    cout << "Test #1 " << "'" << ltrim("") << "'" << endl;
    cout << "Test #2 " << "'" << ltrim("12345") << "'" << endl;
    cout << "Test #3 " << "'" << ltrim("   12345   ") << "'" << endl;
    cout << "Test #4 " << "'" << ltrim("           ") << "'" << endl;
    cout << "Test #5 " << "'" << ltrim("          1") << "'" << endl;
    cout << "Test #6 " << "'" << ltrim("1         1") << "'" << endl;

    // rtrim
    cout << "========================" << endl;
    cout << "rtrim test" << endl;
    cout << "========================" << endl;
    cout << "Test #1 " << "'" << rtrim("") << "'" << endl;
    cout << "Test #2 " << "'" << rtrim("12345") << "'" << endl;
    cout << "Test #3 " << "'" << rtrim("   12345   ") << "'" << endl;
    cout << "Test #4 " << "'" << rtrim("           ") << "'" << endl;
    cout << "Test #5 " << "'" << rtrim("1          ") << "'" << endl;
    cout << "Test #6 " << "'" << rtrim("1         1") << "'" << endl;

    // trim
    cout << "========================" << endl;
    cout << "trim test" << endl;
    cout << "========================" << endl;
    cout << "Test #1 " << "'" << trim("") << "'" << endl;
    cout << "Test #2 " << "'" << trim("12345") << "'" << endl;
    cout << "Test #3 " << "'" << trim("   12345   ") << "'" << endl;
    cout << "Test #4 " << "'" << trim("           ") << "'" << endl;
    cout << "Test #5 " << "'" << trim("          1") << "'" << endl;
    cout << "Test #6 " << "'" << trim("1          ") << "'" << endl;
    cout << "Test #7 " << "'" << trim("1         1") << "'" << endl;
}

//int main()
//{
//    simple();
//    test_stl_helpers_C03();
//    test_stl_helpers_C11();
//    test_stl_helpers_C03_own_type();
//    test_trim();
//}

