/*! \file   	worker.hpp
*	\brief
*
*  \author 		Skident
*  \date   		27.10.2016
*  \copyright	Skident Inc.
*/

#pragma once

#include <thread>
#include <atomic>
#include "eos/thread/event.hpp"

namespace eos
{
	//! Abstract class which 
    class worker
    {
    public:
		//! Default constructor
        worker();

		//! Pure virtual destructor
        virtual ~worker() = 0;

		//! Run task in the new thread
        virtual void run();

		//! Cancel started task
        virtual void cancel();

		//! Waits until task() will be finished.
		//! This method blocks thread.
        virtual void join();

		//! Virtual method which should be overriden 
    	//! by inheritor class.
        virtual void task() = 0;

    protected:
        std::atomic<bool> m_started;	///< true - if task was started, false - not started
        event m_action;					///< event which notifies task about needed action

		//! resets event and marks the worker as not started
		virtual void reset();

    private:
        std::thread m_thread;
    };
}
