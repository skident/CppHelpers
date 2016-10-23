#pragma once

#include <atomic>
#include <mutex>
#include <condition_variable>

namespace eos
{
    class event
    {
    public:
        typedef unsigned long milliseconds;

        class status
        {
            std::atomic<bool> m_canceled;
            std::atomic<bool> m_notofied;
            std::atomic<bool> m_expired;

        public:
            enum eRiseReason
            {
                timeout,
                updates,
                cancellation,
            };

            status();
            status(const status& rhs);
            status& operator=(const status& rhs);
            virtual ~status();

            bool canceled() const;
            bool notified() const;
            bool expired() const;

            bool risen() const;
            void reset();

            void rise(eRiseReason reason);
        };

        event();
        virtual ~event();

        void cancel();
        void notify();

        status wait(const milliseconds& timeout);
        void reset();

        void dump();
    private:
//        std::atomic<bool> m_notification;
        std::mutex m_mutex;
        std::condition_variable m_condVar;
        status m_status;
    };
}

