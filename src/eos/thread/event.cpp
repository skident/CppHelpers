/*! \file   	event.cpp
*	\brief
*
*  \author 		Skident
*  \date   		27.10.2016
*  \copyright	Skident Inc.
*/


#include "eos/thread/event.hpp"

using namespace std;

namespace eos
{
    //////////////////////////////
    /// event::sleeper implementation
    //////////////////////////////
    event::sleeper::sleeper()
    {

    }

    event::sleeper::sleeper(const sleeper& rhs)
    {
        m_canceled.store(rhs.m_canceled);
        m_notified.store(rhs.m_notified);
        m_expired.store(rhs.m_expired);
    }

    event::sleeper& event::sleeper::operator=(const sleeper& rhs)
    {
        if (this != &rhs)
        {
            m_canceled.store(rhs.m_canceled);
            m_notified.store(rhs.m_notified);
            m_expired.store(rhs.m_expired);
        }

        return *this;
    }

    event::sleeper::~sleeper()
    {

    }

    bool event::sleeper::canceled() const
    {
        return m_canceled;
    }

    bool event::sleeper::notified() const
    {
        return m_notified;
    }

    bool event::sleeper::expired() const
    {
        return m_expired;
    }

    bool event::sleeper::awaked() const
    {
         return (canceled() || notified() || expired());
    }

    void event::sleeper::reset()
    {
        m_canceled.store(false);
        m_notified.store(false);
        m_expired.store(false);
    }

    void event::sleeper::shake(eRiseReason reason)
    {
        switch(reason)
        {
        case timeout:
            m_expired.store(true);
            break;

        case updates:
            m_notified.store(true);
            break;

        case cancellation:
            m_canceled.store(true);
            break;
        }
    }

    //////////////////////////////
    /// event implementation
    //////////////////////////////

    event::event()
    {
        reset();
    }

    event::~event()
    {

    }
	
    void event::cancel()
    {
		m_sleeper.shake(sleeper::cancellation);
        unique_lock<mutex> ul(m_mutex);
        m_condVar.notify_all();
    }

    void event::notify()
    {
        m_sleeper.shake(sleeper::updates);
        unique_lock<mutex> ul(m_mutex);
        m_condVar.notify_all();
    }

    event::sleeper event::wait(const milliseconds& timeout)
    {
        auto spuriousProtection = [this]()
        {
            return m_sleeper.awaked() == true;
        };

        {
            bool isNotified;
            unique_lock<mutex> ul(m_mutex);
            isNotified = m_condVar.wait_for(
                                ul,
                                chrono::milliseconds(timeout),
                                spuriousProtection
            );
            if (!isNotified)
                m_sleeper.shake(sleeper::timeout);
        }
        return m_sleeper;
    }

    void event::reset()
    {
        m_sleeper.reset();
    }
}
