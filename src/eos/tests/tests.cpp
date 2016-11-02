//
//  tests.cpp
//  eos
//
//  Created by Skident on 11/1/16.
//
//

#include "eos/tests/tests.hpp"

namespace eos
{
	TestContainer& TestContainer::get()
	{
		static TestContainer self;
		return self;
	}

	void TestContainer::RunAll()
	{
		std::stringstream ss;
		for (const auto& testInfo : m_container)
		{
			auto ptr = testInfo.second;
			
			ss << std::endl << "RUN TEST " << ptr->getName() << "." << ptr->getGroup();
			print(ss.str());
			ss.str("");

			ptr->run();
		}

		ss << std::endl << "Total tests: " << getTotal() << ", Failed: " << getErrors() << ", Success: " << getSuccess() << std::endl;
		print(ss.str());

		clear();
	}


	void TestContainer::RunAllTests()
	{
		TestContainer::get().RunAll();
	}

	TestContainer::TestContainer()
	{
		clear();
	}

	TestContainer::TestContainer(const TestContainer& rhs)
	{
		m_container = rhs.m_container;
		m_errors = rhs.m_errors;
		m_success = rhs.m_success;
	}
	TestContainer& TestContainer::operator=(const TestContainer& rhs)
	{
		if (this != &rhs)
		{
			m_container = rhs.m_container;
			m_errors = rhs.m_errors;
			m_success = rhs.m_success;
		}
		return *this;
	}
	TestContainer::~TestContainer()
	{
		
	}

	void TestContainer::registerTest(std::string name, Test* test)
	{
		if (test)
			m_container.insert(std::make_pair(name, test));
	}

	void TestContainer::incError()
	{
		++m_errors;
	}

	void TestContainer::incSuccess()
	{
		++m_success;
	}

	std::size_t TestContainer::getTotal() const
	{
		return m_success + m_errors;
	}

	std::size_t TestContainer::getErrors() const
	{
		return m_errors;
	}

	std::size_t TestContainer::getSuccess() const
	{
		return m_success;
	}

	void TestContainer::clear()
	{
		m_container.clear();
		m_errors = 0;
		m_success = 0;
	}

	void TestContainer::addSuccess()
	{
		incSuccess();
		std::stringstream ss;
		ss << "\t[SUCCESS]" << std::endl;
		print(ss.str());
	}

	void TestContainer::print(const std::string& msg) 
	{
		std::cout << msg;
	}

	///////////////////////////////////////////////

	Test::Test(std::string name, std::string group)
		: m_name(name)
		, m_group(group)
	{
		TestContainer::get().registerTest(name, this);
	}

	Test::~Test()
	{
		
	}

	std::string Test::getName() const
	{
		return m_name;
	}

	std::string Test::getGroup() const
	{
		return m_group;
	}
}

