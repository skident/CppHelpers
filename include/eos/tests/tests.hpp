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
#include <iostream>
#include <sstream>

namespace eos
{
    class Test
    {
    public:
        Test(std::string name, std::string group);
        
		virtual ~Test();
        
        virtual void run() = 0;
        
		std::string getName() const;        
		std::string getGroup() const;

    protected:
        std::string m_name;
        std::string m_group;
    };
	


    class TestContainer
    {
		
    public:
		static TestContainer& get();
		void RunAll();
		static void RunAllTests();

		template<class T>
		void addFailure(	const std::string& name,
							const std::string& group,
							const std::string& fileName,
							const std::size_t& line,
							T expected,
							T current
				)
		{
			incError();

			std::stringstream ss;
			ss << "\t[FAILED]" << std::endl;
			ss << fileName << ":" << line << std::endl;
			ss << "Expected value: " << expected << ", Real value: " << current << std::endl;

			print(ss.str());
		}


		void addSuccess();


    private:
		friend class Test;
        std::multimap<std::string, Test*> m_container;
		std::size_t m_errors;
		std::size_t m_success;
        
		TestContainer();
		TestContainer(const TestContainer& rhs);
		TestContainer& operator=(const TestContainer& rhs);
		~TestContainer();

		void registerTest(std::string name, Test* test);

		void incError();

		void incSuccess();

		std::size_t getTotal() const;

		std::size_t getErrors() const;

		std::size_t getSuccess() const;

		void clear();

		static void print(const std::string& msg);
    };
    
    /////////////////

}



#define TEST(name, group)																				\
    class name##group##Test : public eos::Test															\
    {																									\
    public:																								\
        name##group##Test()																				\
            : Test(#name, #group)																		\
        {}																								\
        ~name##group##Test() {}																			\
        void run() override;																			\
    };																									\
																										\
    name##group##Test name##group##Instance = name##group##Test();										\
    void name##group##Test::run()																		\


#define EQ_TEST(expected, current)																		\
    {																									\
        if (expected != current)																		\
            TestContainer::get().addFailure(m_name, m_group, __FILE__, __LINE__, #expected, #current);	\
		else																							\
			TestContainer::get().addSuccess();															\
    }																									\


