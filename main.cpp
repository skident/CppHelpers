#include "stl_helper.h"

using namespace stl_helper;
using namespace std;

void test_stl_helpers_C11()
{
#if __cplusplus >= 201103L 
	cout << "=========================================" << endl;
	cout << "Test of stl_helpers for C++11 and greater" << endl;
	cout << "=========================================" << endl;

	// 1. Test vector
	vector<string> vecStr = {"111", "222", "333"};
	print(vecStr);
	
	
	// 2. Test list
	list<int> listInt = {111, 222, 333};
	print(listInt);
	
	
	// 3. Test set
	set<int> setInt = {1,2,3,4,5,6};
	print(setInt);
	
	
	// 4. Test map
	map<int, string> mapIntStr = {{111, "q"},{222, "w"}, {333, "z"}};
	print(mapIntStr);
	
	
	// 5. Test unordered_set
	unordered_set<int> usetInt = {8,6,5,4,3,2};
	print(usetInt);
	
	
	// 6. Test unordered_map
	unordered_map<int, string> umapIntStr = {{11, "qss"}, {22, "wss"}, {33, "zss"}};
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
	print(vecStr);
	
	// 2. Test list
	list<int> listInt;
	listInt.push_back(1);
	listInt.push_back(95);
	listInt.push_back(33);
	print(listInt);
	
	list<string> listStr;
	listStr.push_back("1");
	listStr.push_back("95");
	listStr.push_back("33");
	print(listStr);

	
	// 3. Test set
	set<int> setInt;
	setInt.insert(4);
	setInt.insert(5);
	print(setInt);
	
	
	// 4. Test map
	map<int, string> mapIntStr;
	mapIntStr[11] = "ssss";
	mapIntStr[911] = "sx";
	mapIntStr[124] = "sssefrg";
	mapIntStr[01] = "45448";
	mapIntStr[19] = "3434t";
	print(mapIntStr);
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

int main()
{
	test_stl_helpers_C03();
	test_stl_helpers_C11();
	test_stl_helpers_C03_own_type();
}
