#pragma once

#include <thread>
#include "event.hpp"

namespace eos
{
    class worker
    {
    public:
        worker();
        virtual ~worker() = 0;

        virtual void run();
        virtual void cancel();
        virtual void join();

        virtual void task() = 0;

    protected:
//        std::atomic<bool> m_canceled;
        std::atomic<bool> m_started;
        event m_action;

       virtual void reset();

    private:
        std::thread m_thread;
    };
}

