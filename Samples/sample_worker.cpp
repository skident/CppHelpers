#include "sample_worker.hpp"

#include <iostream>
#include <memory>

using namespace std;

test_task::test_task()
{

}

test_task::~test_task()
{

}

void test_task::task()
{
    for (;;)
    {
        // do some work
        auto state = m_action.wait(1000);
        if (state.canceled())
        {
            cout << "Cancelled" << endl;
            break;
        }

        if (state.notified())
        {
            cout << "Notified" << endl;
        }

        if (state.expired())
        {
            // timeout
            cout << "Timeout" << endl;
        }
    }
}



void sample_worker_usage()
{
    unique_ptr<eos::worker> work1(new test_task());
    work1->run();

    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "Send cancel signal!" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));

    work1->cancel();
    work1->join();
}
