#pragma once

#include "eos/thread/worker.hpp"

class test_task : public eos::worker
{
public:
    test_task();
    ~test_task();

    void task() override;
};


void sample_worker_usage();
