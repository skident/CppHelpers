#include <iostream>

#include "sample_output.hpp"
#include "sample_range.hpp"
#include "sample_wire.hpp"
#include "sample_worker.hpp"

#include <eos/types/tests.hpp>

using namespace std;
using namespace eos;


TEST(test1, just)
{
    EQ_TEST(1,4)
}

int main()
{
    TestContainer::get().RunAll();
    
    /*
	run_output_samples();
	run_range_samples();
    run_wire_samples();
    sample_worker_usage();
     */
}
