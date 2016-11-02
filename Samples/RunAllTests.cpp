#include <iostream>

#include "sample_output.hpp"
#include "sample_range.hpp"
#include "sample_wire.hpp"
#include "sample_worker.hpp"

#include <eos/tests/tests.hpp>

using namespace std;
using namespace eos;


TEST(test, ints)
{
    EQ_TEST(1,4)
}

TEST(test, strings)
{
	EQ_TEST(string("123"), "123")
}

int main()
{
	TestContainer::RunAllTests();
    
    /*
	run_output_samples();
	run_range_samples();
    run_wire_samples();
    sample_worker_usage();
     */
}
