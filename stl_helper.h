/*! \file   stl_helper.h
	\brief	Useful functions for work with STL containers. 
			1. Now it supports generic print for STL containers (vector, list, map) like: [elem1, elem2, elem3]
			2. And syntax sugar for checking is element exists in std::vector, usage: if (x in container) ..

    \author Skident
    \date   02.09.2016
*/

#

#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <sstream>


// check is the C++11 or greater available (special hack for MSVC)
#if (defined(_MSC_VER) && __cplusplus >= 199711L) || __cplusplus >= 201103L
	#define MODERN_CPP_AVAILABLE 1
#endif


#ifdef MODERN_CPP_AVAILABLE
	#include <unordered_set>
	#include <unordered_map>
#endif


namespace stl_helper
{
	#define in &&  // make the alias for operator && an call it "in"

	//! Search the element elem in conrainer and return true if found and false if not found.
	//! \param elem element which should be checked for presence in collection
	//! \param collection generic collection of elements with type T. 
	//! \return true if element found in collection and false - otherwise
	//! Usage: if (4 in myVec) doSomething();
	template <class T>
	bool operator in(T elem, const std::vector<T>& collection)
	{
		for(typename std::vector<T>::const_iterator it = collection.begin(); it != collection.end(); ++it)
		{
			if (elem == *it)
				return true;
		}
		return false;
	}
	

	//! Prints std::vector<T> as in Python
	//! \param collection which should be printed
	//! \param elem_separator the separator which will be inserted between elements of collection
	//! \param first_bracket data before collection's elements (usual it is the parenthesis, square or curly bracker '(', '[', '{')
	//! \param last_bracket data after collection's elements (usual it is the parenthesis, square or curly bracker ')', ']', '}')
	template<class T>
	void print(const std::vector<T>& collection, std::string elem_separator = ", ", std::string first_bracket = "[", std::string last_bracket = "]")
	{
		std::stringstream ss;
		for(typename std::vector<T>::const_iterator it = collection.begin(); it != collection.end(); ++it)
		{
			ss << T(*it) << elem_separator;
		}

		std::string data = ss.str();
		if (!data.empty() && !elem_separator.empty())
			data = data.substr(0, data.rfind(elem_separator));

		std::cout << first_bracket << data << last_bracket << std::endl;
	}

	//! Prints std::list<T> as in Python
	//! \param collection which should be printed
	//! \param elem_separator the separator which will be inserted between elements of collection
	//! \param first_bracket data before collection's elements (usual it is the parenthesis, square or curly bracker '(', '[', '{')
	//! \param last_bracket data after collection's elements (usual it is the parenthesis, square or curly bracker ')', ']', '}')
	template<class T>
	void print(const std::list<T>& collection, std::string elem_separator = ", ", std::string first_bracket = "[", std::string last_bracket = "]")
	{
		std::stringstream ss;
		for(typename std::list<T>::const_iterator it = collection.begin(); it != collection.end(); ++it)
		{
			ss << *it << elem_separator;
		}

		std::string data = ss.str();
		if (!data.empty())
			data.resize(data.length()-elem_separator.length());
			//data = data.substr(0, data.rfind(elem_separator));

		std::cout << first_bracket << data << last_bracket << std::endl;
	}

	//! Prints std::set<T> as in Python
	//! \param collection which should be printed
	//! \param elem_separator the separator which will be inserted between elements of collection
	//! \param first_bracket data before collection's elements (usual it is the parenthesis, square or curly bracker '(', '[', '{')
	//! \param last_bracket data after collection's elements (usual it is the parenthesis, square or curly bracker ')', ']', '}')
	template<class T>
	void print(const std::set<T>& collection, std::string elem_separator = ", ", std::string first_bracket = "[", std::string last_bracket = "]")
	{
		std::stringstream ss;
		for(typename std::set<T>::const_iterator it = collection.begin(); it != collection.end(); ++it)
		{
			ss << *it << elem_separator;
		}

		std::string data = ss.str();
		if (!data.empty() && !elem_separator.empty())
			data = data.substr(0, data.rfind(elem_separator));

		std::cout << first_bracket << data << last_bracket << std::endl;
	}


	//! Prints std:map<T, U> as in Python
	//! \param collection which should be printed
	//! \param elem_separator the separator which will be inserted between elements of collection
	//! \param keyval_separator separator between key and value of map. For default it is the '=>'
	//! \param first_bracket data before collection's elements (usual it is the parenthesis, square or curly bracker '(', '[', '{')
	//! \param last_bracket data after collection's elements (usual it is the parenthesis, square or curly bracker ')', ']', '}')
	template<class T, class U>
	void print(const std::map<T, U>& collection, std::string elem_separator = ", ",	std::string keyval_separator = " => ", std::string first_bracket = "[", std::string last_bracket = "]")
	{
		std::stringstream ss;
		for(typename std::map<T, U>::const_iterator it = collection.begin(); it != collection.end(); ++it)
		{
			ss << it->first << keyval_separator << it->second <<  elem_separator;
		}

		std::string data = ss.str();
		if (!data.empty() && !elem_separator.empty())
			data = data.substr(0, data.rfind(elem_separator));

		std::cout << first_bracket << data << last_bracket << std::endl;
	}


	// Only for modern C++ 
#ifdef MODERN_CPP_AVAILABLE
	//! Prints std::unordered_set<T> as in Python
	//! \param collection which should be printed
	//! \param elem_separator the separator which will be inserted between elements of collection
	//! \param first_bracket data before collection's elements (usual it is the parenthesis, square or curly bracker '(', '[', '{')
	//! \param last_bracket data after collection's elements (usual it is the parenthesis, square or curly bracker ')', ']', '}')
	template<class T>
	void print(const std::unordered_set<T>& collection, std::string elem_separator = ", ", std::string first_bracket = "[", std::string last_bracket = "]")
	{
		std::stringstream ss;
		for(typename std::unordered_set<T>::const_iterator it = collection.begin(); it != collection.end(); ++it)
		{
			ss << *it << elem_separator;
		}

		std::string data = ss.str();
		if (!data.empty() && !elem_separator.empty())
			data = data.substr(0, data.rfind(elem_separator));

		std::cout << first_bracket << data << last_bracket << std::endl;
	}

	//! Prints std:unordered_map<T, U> as in Python
	//! \param collection which should be printed
	//! \param elem_separator the separator which will be inserted between elements of collection
	//! \param keyval_separator separator between key and value of map. For default it is the '=>'
	//! \param first_bracket data before collection's elements (usual it is the parenthesis, square or curly bracker '(', '[', '{')
	//! \param last_bracket data after collection's elements (usual it is the parenthesis, square or curly bracker ')', ']', '}')
	template<class T, class U>
	void print(const std::unordered_map<T, U>& collection, std::string elem_separator = ", ",	std::string keyval_separator = " => ", std::string first_bracket = "[", std::string last_bracket = "]")
	{
		std::stringstream ss;
		for(typename std::unordered_map<T, U>::const_iterator it = collection.begin(); it != collection.end(); ++it)
		{
			ss << it->first << keyval_separator << it->second <<  elem_separator;
		}

		std::string data = ss.str();
		if (!data.empty() && !elem_separator.empty())
			data = data.substr(0, data.rfind(elem_separator));

		std::cout << first_bracket << data << last_bracket << std::endl;
	}
#endif

};
