//
//  tests.hpp
//  eos
//
//  Created by Skident on 11/1/16.
//
//

#pragma once

#include <map>
#include <string>
#include <tuple>
#include <functional>
#include <iostream>

namespace eos
{
    class Test
    {
    public:
        Test(std::string name, std::string group);
        /*
        : m_name(name)
        , m_group(group)
        {
            TestContainer::get().registerTest(name, this);
        }
         */
        
        virtual ~Test()
        {
            
        }
        
        virtual void run() = 0;
        
        std::string getName() const
        {
            return m_name;
        }
        
        std::string getGroup() const
        {
            return m_group;
        }
        
    protected:
        std::string m_name;
        std::string m_group;
    };

    
    class TestContainer
    {
    public:
        static TestContainer& get()
        {
            static TestContainer self;
            return self;
        }
        
        void registerTest(std::string name, Test* test)
        {
            if (test)
                m_container.insert(std::make_pair(name, test));
        }
        
        void RunAll()
        {
            for (const auto& testInfo : m_container)
            {
                auto ptr = testInfo.second;
                std::cout << "RUN TEST " << ptr->getName() << "." << ptr->getGroup() << std::endl;
                ptr->run();
            }
            
            // TODO: analyze Failures
            
        }
        
    private:
        std::multimap<std::string, Test*> m_container;
        
        TestContainer(){}
        TestContainer(const TestContainer& rhs){}
        TestContainer& operator=(const TestContainer& rhs)
        {
            return *this;
        }
        ~TestContainer() {}
    };
    
    /////////////////
    Test::Test(std::string name, std::string group)
        : m_name(name)
        , m_group(group)
    {
        TestContainer::get().registerTest(name, this);
    }
    /////////////////
    
    
    
    class Failures
    {
    public:
        static Failures& get()
        {
            static Failures self;
            return self;
        }
        
        template<class T>
        void add(std::string name,
                 std::string group,
                 std::string fileName,
                 std::size_t line,
                 T expected,
                 T current
                )
        {
            incError();
            std::cout << "FAILED: " << fileName << ":" << line << std::endl;
            std::cout << "Expected value: " << expected << " Real value: " << current << std::endl;
        }
        
        std::size_t getTotal() const
        {
            return m_errors;
        }
        
    private:
        std::size_t m_errors;
        
        void incError()
        {
            ++m_errors;
        }
        
        Failures() {}
        ~Failures() {}
        Failures(const Failures& rhs) {}
        Failures& operator=(const Failures& rhs)
        {
            return *this;
        }
    };
}



#define TEST(name, group)                                                               \
    class name##group##Test : public eos::Test                                          \
    {                                                                                   \
    public:                                                                             \
        name##group##Test()                                                             \
            : Test(#name, #group)                                                       \
        {}                                                                              \
        ~name##group##Test() {}                                                         \
        void run() override;                                                            \
    };                                                                                  \
                                                                                        \
    name##group##Test name##group##Instance = name##group##Test();                      \
    void name##group##Test::run()                                                       \


#define EQ_TEST(expected, current)                                                      \
    {                                                                                   \
     if (expected != current)                                                           \
        Failures::get().add(m_name, m_group, __FILE__, __LINE__, #expected, #current);  \
    }                                                                                   \
