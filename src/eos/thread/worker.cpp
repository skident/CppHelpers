/*! \file   	worker.cpp
*	\brief
*
*  \author 		Skident
*  \date   		27.10.2016
*  \copyright	Skident Inc.
*/


#include "eos/thread/worker.hpp"

using namespace std;

namespace eos
{
    worker::worker()
    {
        m_started.store(false);
    }

    worker::~worker()
    {

    }

    void worker::run()
    {
        if (m_started)
            return;

        thread tmpThread(&worker::task, this);
        m_thread.swap(tmpThread);
        m_started.store(true);
    }


    void worker::cancel()
    {
        m_action.cancel();
    }

    void worker::join()
    {
        if (!m_started)
        {
            return;
        }

        m_thread.join();
        reset();
    }

    void worker::reset()
    {
        m_started.store(false);
        m_action.reset();
    }

}
