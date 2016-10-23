#include "worker.hpp"
#include <iostream>

using namespace std;

namespace eos
{
    worker::worker()
    {
//        m_canceled.store(false);
        m_started.store(false);

        cout << "Worker has born" << endl;
    }

    worker::~worker()
    {
        cout << "Worker died" << endl;
    }

    void worker::run()
    {
        cout << "Running..." << endl;
        if (m_started)
            return;

        std::thread tmpThread(&worker::task, this);
        m_thread.swap(tmpThread);

        m_started.store(true);
        cout << "Thread works..." << endl;
    }

//    void worker::task() //= 0;
//    {
//        for (;;)
//        {
//            // do some work
//            auto state = m_action.wait(1000);
//            if (state.canceled())
//                break;

//            if (state.notified())
//            {
//                // do something
//            }

//            if (state.expired())
//            {
//                // timeout
//            }
//        }
//    }

    void worker::cancel()
    {
        cout << "Cancel received!" << endl;
//        m_canceled.store(true);

        m_action.cancel();
    }

    void worker::join()
    {
        cout << "Join will be called" << endl;
        if (!m_started)
        {
            cout << "task wasn't started" << endl;
            return;
        }

        m_thread.join();

        reset();

        cout << "Joined" << endl;
    }

    void worker::reset()
    {
//        m_canceled.store(false);
        m_started.store(false);
        m_action.reset();
    }



}
