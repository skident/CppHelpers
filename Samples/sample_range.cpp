#include "eos/types/range.hpp"
#include <iostream>
#include <vector>
#include "samples.hpp"

using namespace std;

void sample_range_1()
{
	cout << endl;
	cout << "=========================================" << endl;
	cout << "     Sample of eos::types::range usage   " << endl;
	cout << "=========================================" << endl;

    eos::range<int> range;

	range.insert({1, 3});
	range.insert({1, 7});
	range.insert({8, 11});

	//range.print();
	cout << range << endl;

	vector<int> values;
	for (int i = 0; i < 15; i++)
		values.push_back(i);
	
	for (auto value : values)
	{
		auto isFind = range.find(value);
		cout << "Value " << value;
		if (!isFind)
			cout << " not";
		cout << " found in range" << endl;
	}
	
}


void run_range_samples()
{
	sample_range_1();	
}
