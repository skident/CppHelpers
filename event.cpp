#include "event.hpp"
#include <iostream>

using namespace std;

namespace eos
{
    //////////////////////////////
    /// event::status implementation
    //////////////////////////////
    event::status::status()
    {

    }

    event::status::status(const status& rhs)
    {
        m_canceled.store(rhs.m_canceled);
        m_notofied.store(rhs.m_notofied);
        m_expired.store(rhs.m_expired);
    }

    event::status& event::status::operator=(const status& rhs)
    {
        if (this != &rhs)
        {
            m_canceled.store(rhs.m_canceled);
            m_notofied.store(rhs.m_notofied);
            m_expired.store(rhs.m_expired);
        }

        return *this;
    }

    event::status::~status()
    {

    }

    bool event::status::canceled() const
    {
        return m_canceled;
    }

    bool event::status::notified() const
    {
        return m_notofied;
    }

    bool event::status::expired() const
    {
        return m_expired;
    }

    bool event::status::risen() const
    {
         return (canceled() || notified() || expired());
    }

    void event::status::reset()
    {
        m_canceled.store(false);
        m_notofied.store(false);
        m_expired.store(false);
    }

    void event::status::rise(eRiseReason reason)
    {
        switch(reason)
        {
        case timeout:
            m_expired.store(true);
            break;

        case updates:
            m_notofied.store(true);
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
        cout << "event::cancel" << endl;
        m_status.rise(status::cancellation);
//        m_canceled.store(true);
         dump();
         std::unique_lock<std::mutex> ul(m_mutex);
         m_condVar.notify_all();
    }

    void event::notify()
    {
         cout << "event::notify" << endl;
         m_status.rise(status::updates);
//        m_notification.store(true);
        std::unique_lock<std::mutex> ul(m_mutex);
        m_condVar.notify_all();
    }

    event::status event::wait(const milliseconds& timeout)
    {
        auto spuriousProtection = [this]()
        {
            return m_status.risen() == true;
        };

        {
            bool isNotified;
            std::unique_lock<std::mutex> ul(m_mutex);
            isNotified = m_condVar.wait_for(
                                ul,
                                std::chrono::milliseconds(timeout),
                                spuriousProtection
            );
            if (!isNotified)
                m_status.rise(status::timeout);
        }

        dump();
        return m_status;
    }

    void event::reset()
    {
        m_status.reset();
    }



    void event::dump()
    {
        cout << "canceled: " << m_status.canceled()
             << " notified: " << m_status.notified()
             << " expired: " << m_status.expired() << endl;
    }
}
