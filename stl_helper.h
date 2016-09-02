/*! \file   stl_helper.h
	\brief	Useful functions for work with STL containers. 
			1. Now it supports generic print for STL containers (vector, list, map) like: [elem1, elem2, elem3]
			2. And syntax sugar for checking is element exists in std::vector, usage: if (x in container) ..

    \author Skident
    \date   02.09.2016
*/

#include <iostream>
#include <sstream>
#include <map>


// check is the C++11 or greater available (special hack for MSVC)
#if (defined(_MSC_VER) && __cplusplus >= 199711L) || __cplusplus >= 201103L
	#define MODERN_CPP_AVAILABLE 1
#endif


#ifdef MODERN_CPP_AVAILABLE
	#include <unordered_map>
#endif


namespace stl_helper
{
	//! Prints std::Container<T> as in Python
	//! \param collection which should be printed
	//! \param elem_separator the separator which will be inserted between elements of collection
	//! \param first_bracket data before collection's elements (usual it is the parenthesis, square or curly bracker '(', '[', '{')
	//! \param last_bracket data after collection's elements (usual it is the parenthesis, square or curly bracker ')', ']', '}')
	template<class Container>
	void print(const Container& collection, std::string elem_separator = ", ", std::string first_bracket = "[", std::string last_bracket = "]")
	{
		std::stringstream ss;
		typename Container::const_iterator it = collection.begin();
		for (; it != collection.end(); ++it)
		//for(typename std::vector<T>::const_iterator it = collection.begin(); it != collection.end(); ++it)
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
