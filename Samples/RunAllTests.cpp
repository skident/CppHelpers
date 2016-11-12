#include <iostream>

#include "samples.hpp"
#include "sample_worker.hpp"

using namespace std;


int main()
{
	run_output_samples();
	run_range_samples();
    run_wire_samples();
    run_optional_samples();
    //sample_worker_usage();

}
