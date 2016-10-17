/*! \file   	stl_helper.h
 *	\brief		Useful functions for work with STL containers. 
 *			
 *	Now it supports generic print for STL containers like: [elem1, elem2, elem3]
 *	Supported STL conrainers: vector, deque, list, set, unordered_set, map,
 *	unordered_map, array
 *
 *  \author 	Skident
 *  \date   	02.09.2016
 *  \copyrigth	Skident Inc.
 */

// check is the C++11 or greater available (special hack for MSVC)
#if (defined(_MSC_VER) && __cplusplus >= 199711L) || __cplusplus >= 201103L
	#define MODERN_CPP_AVAILABLE 1
#endif


#include <iostream>
#include <sstream>
#include <map>
#include <cctype>

#ifdef MODERN_CPP_AVAILABLE
	#include <unordered_map>
#endif

#define BUILD_CONTENT 														\
    	std::stringstream ss;												\
	    for (; it != collection.end(); ++it)								\
		{																	\
			ss << *it << elem_separator;									\
		}																	\


#define BUILD_MAP_CONTENT 													\
    	std::stringstream ss;												\
	    for (; it != collection.end(); ++it)								\
		{																	\
			ss 	<< it->first 												\
				<< keyval_separator											\
				<< it->second 												\
				<< elem_separator;											\
		}																	\


#define PRINT_CONTENT														\
		std::string data = ss.str();										\
		if (!data.empty() && !elem_separator.empty())						\
			data = data.substr(0, data.rfind(elem_separator));				\
		std::cout << first_bracket << data << last_bracket << std::endl;	\


namespace eos
{
	//! Prints std::Container<T> as in Python
	//! Supported containers: vector, deque, list, set, unordered_set(C++11), forward_list(C++11)
	//! \param collection which should be printed
	//! \param elem_separator the separator which will be inserted between elements of collection
	//! \param first_bracket data before collection's elements (usual it is the parenthesis, square or curly bracker '(', '[', '{')
	//! \param last_bracket data after collection's elements (usual it is the parenthesis, square or curly bracker ')', ']', '}')
	template<class Container>
	void print(const Container& collection, 
				std::string elem_separator = ", ", 
				std::string first_bracket = "[", 
				std::string last_bracket = "]"
			)
	{
		typename Container::const_iterator it = collection.begin();
		BUILD_CONTENT
		PRINT_CONTENT
	}

	//! Prints std:map<T, U> as in Python
	//! \param collection which should be printed
	//! \param elem_separator the separator which will be inserted between elements of collection
	//! \param keyval_separator separator between key and value of map. For default it is the '=>'
	//! \param first_bracket data before collection's elements (usual it is the parenthesis, square or curly bracker '(', '[', '{')
	//! \param last_bracket data after collection's elements (usual it is the parenthesis, square or curly bracker ')', ']', '}')
	template<class T, class U>
	void print(const std::map<T, U>& collection,
				std::string elem_separator = ", ",	
				std::string keyval_separator = " => ", 
				std::string first_bracket = "[",
				std::string last_bracket = "]"
		)
	{
		typename std::map<T, U>::const_iterator it = collection.begin(); 
		BUILD_MAP_CONTENT
		PRINT_CONTENT
	}

	//! Prints std:array<T, Size> as in Python
	//! \param collection which should be printed
	//! \param elem_separator the separator which will be inserted between elements of collection
	//! \param keyval_separator separator between key and value of map. For default it is the '=>'
	//! \param first_bracket data before collection's elements (usual it is the parenthesis, square or curly bracker '(', '[', '{')
	//! \param last_bracket data after collection's elements (usual it is the parenthesis, square or curly bracker ')', ']', '}')
	template<template <class T, std::size_t N> class Array, class Type, std::size_t Size>
	void print(const Array<Type, Size>& collection,
				std::string elem_separator = ", ", 
				std::string first_bracket = "[", 
				std::string last_bracket = "]"
			)
	{
		typename Array<Type, Size>::const_iterator it = collection.begin();
		BUILD_CONTENT
		PRINT_CONTENT
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
	void print(const std::unordered_map<T, U>& collection, 
				std::string elem_separator = ", ",	
				std::string keyval_separator = " => ", 
				std::string first_bracket = "[",
				std::string last_bracket = "]"
		)
	{
		
		typename std::unordered_map<T, U>::const_iterator it = collection.begin();
		BUILD_MAP_CONTENT
		PRINT_CONTENT
	}


#endif

	//! Removes all whitespaces before data in string.
	//! \param str string with data
	//! \return string without whitespaces in left part
	std::string ltrim(const std::string& str)
	{
		std::string result;
		std::size_t len = str.length();
		std::size_t i = 0;
		for ( ; i < len; i++)
		{
			if (std::isspace(str[i]) == 0)
				break;
		}

		if (i < len)
			result = str.substr(i);
		return result;
	}

	//! Removes all whitespaces after data in string
	//! \param str string with data
	//! \return string without whitespaces in right part
	std::string rtrim(const std::string& str)
	{
		std::string result;
		std::size_t len = str.length();
		std::size_t i = len-1;
		for ( ; i >= 0; i--)
		{
			if (std::isspace(str[i]) == 0)
				break;
		}

		result = str.substr(0, i+1);
		return result;
	}

	//! Removes all whitespaces before and after data in string
	//! \param str string with data
	//! \return string without whitespaces before and after data in string
	std::string trim(const std::string& str)
	{
		std::string result = ltrim(str);
		result = rtrim(result);
		return result;
	}
};
