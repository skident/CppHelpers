/*! \file   	event.hpp
*	\brief		
*
*  \author 		Skident
*  \date   		27.10.2016
*  \copyright	Skident Inc.
*/


#pragma once

#include <atomic>
#include <mutex>
#include <condition_variable>

namespace eos
{
	//! Class represents the event for worker class.
    class event
    {
    public:
        typedef unsigned long milliseconds; ///< alias for reperesent the milliseconds

		//! Possible statuses of event
        class sleeper
        {
            std::atomic<bool> m_canceled;	
            std::atomic<bool> m_notified;	
            std::atomic<bool> m_expired;	

        public:
			//! Reasons for event
            enum eRiseReason
            {
                timeout,
                updates,
                cancellation,
            };

			//! Default constructor
            sleeper();

			//! Copy constructor
            sleeper(const sleeper& rhs);

			//! Assignment operator
            sleeper& operator=(const sleeper& rhs);

			//! Destructor
            virtual ~sleeper();

			//! Checks if the canceled flag was awaked
			//! \return true - if need to cancel
            bool canceled() const;

			//! Checks if the notify flag was awaked
			//! \return true - if was set, false - otherwise
            bool notified() const;

			//! \return true - if neither cancellation nor notification not received
            bool expired() const;

			//! \return true if any possible notification was received
            bool awaked() const;

			//! reset all flags (all events types will be set as non-happend)
            void reset();

			//! Shake the sleeper for one of reason
            void shake(eRiseReason reason);
        };

		//! Default contructor
        event();

		//! Destructor
        virtual ~event();

		//! Cancel event
        void cancel();

		//! notify 
        void notify();

		//! thread will be sleep for timeout
		//! \param timeout timeout for sleeping in milliseconds
		//! \return reason of wake up
        sleeper wait(const milliseconds& timeout);

		//! Reset the event 
        void reset();

   	private:
        std::mutex m_mutex;
        std::condition_variable m_condVar;
        sleeper m_sleeper;
    };
}

