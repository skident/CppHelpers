#pragma once

#include "worker.hpp"

class test_task : public eos::worker
{
public:
    test_task();
    ~test_task();

    void task() override;
};

