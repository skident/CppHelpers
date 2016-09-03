/*! \file   	stl_helper.h
	\brief		Useful functions for work with STL containers. 
			
	Now it supports generic print for STL containers like: [elem1, elem2, elem3]
	Supported STL conrainers: vector, deque, list, set, unordered_set, map,
	unordered_map, array

    \author 	Skident
    \date   	02.09.2016
    \copyrigth	Skident Inc.
*/

// check is the C++11 or greater available (special hack for MSVC)
#if (defined(_MSC_VER) && __cplusplus >= 199711L) || __cplusplus >= 201103L
	#define MODERN_CPP_AVAILABLE 1
#endif


#include <iostream>
#include <sstream>
#include <map>

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


namespace stl_helper
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


	// Print std::array handler
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

};