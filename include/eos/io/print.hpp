/*! \file   	print.hpp
 *	\brief		Useful functions for work with STL containers. 
 *			
 *	Now it supports generic print for STL containers like: [elem1, elem2, elem3]
 *	Supported STL conrainers: vector, deque, list, set multiset, unordered_set,
 *  map, multimap, unordered_map, array
 *
 *  \author 	Skident
 *  \date   	02.09.2016
 *  \copyright	Skident Inc.
 */

#pragma once

// check is the C++11 or greater available (special hack for MSVC)
#if (defined(_MSC_VER) && __cplusplus >= 199711L) || __cplusplus >= 201103L
	#define MODERN_CPP_AVAILABLE 1
#endif


#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <set>
#include <list>
#include <map>
#include <cctype>

#ifdef MODERN_CPP_AVAILABLE
    #include <array>
    #include <unordered_set>
	#include <unordered_map>
    #include <forward_list>
#endif


#define dump(value) std::cout << (#value) << ": " << (value) << std::endl

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


#define COMPILE_CONTENT														\
        std::string data = ss.str();										\
        if (!data.empty() && !elem_separator.empty())						\
            data = data.substr(0, data.rfind(elem_separator));				\
        std::string result = first_bracket + data + last_bracket;       	\
        os << result;                                                       \
        if (needEndl)                                                       \
            os << std::endl;                                                \



////
///
///
/// Template definitions
///
///

//generic template for classes: deque, list, forward_list, vector
#define VECTOR_AND_CO_TEMPLATE                                          \
    template<                                                           \
        template<class T,                                               \
                 class Alloc = std::allocator<T> >                      \
        class Container, class Type, class Alloc>                       \

#define SET_TEMPLATE                                                    \
    template<                                                           \
        template<class T,                                               \
                 class Compare = std::less<T>,                          \
                 class Alloc = std::allocator<T> >                      \
            class Container, class T, class Compare, class Alloc>       \

#define USET_TEMPLATE                                                   \
    template<                                                           \
template < class Key,                                                   \
           class Hash = std::hash<Key>,                                 \
           class Pred = std::equal_to<Key>,                             \
           class Alloc = std::allocator<Key>                            \
           >                                                            \
    class Container, class Key, class Hash, class Pred, class Alloc     \
    >                                                                   \


#define MAP_TEMPLATE                                                    \
    template<                                                           \
        template<class Key,                                             \
                class T,                                                \
                class Compare = std::less<Key>,                         \
                class Alloc = std::allocator<std::pair<const Key,T> >   \
                >                                                       \
        class Container, class Key,                                     \
        class Value/*, class Compare, class Alloc*/>                    \


#define UMAP_TEMPLATE                                                   \
    template<                                                           \
        template<class Key,                                             \
                   class T,                                             \
                   class Hash = std::hash<Key>,                         \
                   class Pred = std::equal_to<Key>,                     \
                   class Alloc = std::allocator<std::pair<const Key,T> >\
                 >                                                      \
        class Container, class Key, class Value,                        \
        class Hash, class Pred, class Alloc                             \
                >                                                       \


#define ARRAY_TEMPLATE                                                  \
    template<                                                           \
        template<class T, std::size_t N>                                \
        class Array, class Type, std::size_t Size>                      \



namespace eos
{
    static const std::string default_elem_separator     = ", ";
    static const std::string default_keyval_separator   = " => ";
    static const std::string default_first_bracket      = "[";
    static const std::string default_last_bracket       = "]";


    //! Prints template Container<T> as in Python
	//! Supported containers: vector, deque, list, set, unordered_set(C++11), forward_list(C++11)
	//! \param collection which should be printed
	//! \param elem_separator the separator which will be inserted between elements of collection
	//! \param first_bracket data before collection's elements (usual it is the parenthesis, square or curly bracker '(', '[', '{')
	//! \param last_bracket data after collection's elements (usual it is the parenthesis, square or curly bracker ')', ']', '}')
    template<class Container>
    void print( const Container& collection
              , const std::string& elem_separator   = default_elem_separator
              , const std::string& first_bracket    = default_first_bracket
              , const std::string& last_bracket     = default_last_bracket
              , std::ostream& os = std::cout
              , bool needEndl = true
            )
    {
        typename Container::const_iterator it = collection.begin();
        BUILD_CONTENT
        COMPILE_CONTENT
    }


    //! Prints collections with one template argument and allocator as in Python.
    //! Supported standard collections: vector, deque, list, forward_list
    //! \param collection which should be printed
    //! \param elem_separator the separator which will be inserted between elements of collection
    //! \param keyval_separator separator between key and value of map. For default it is the '=>'
    //! \param first_bracket data before collection's elements (usual it is the parenthesis, square or curly bracker '(', '[', '{')
    //! \param last_bracket data after collection's elements (usual it is the parenthesis, square or curly bracker ')', ']', '}')
    VECTOR_AND_CO_TEMPLATE
    void print( const Container<Type>& collection
              , const std::string& elem_separator   = default_elem_separator
              , const std::string& first_bracket    = default_first_bracket
              , const std::string& last_bracket     = default_last_bracket
              , std::ostream& os = std::cout
              , bool needEndl = true
            )
    {
        typename Container<Type>::const_iterator it = collection.begin();
        BUILD_CONTENT
        COMPILE_CONTENT
    }


    //! Prints collections like std:set<T, Compare, Alloc> as in Python
    //! \param collection which should be printed
    //! \param elem_separator the separator which will be inserted between elements of collection
    //! \param keyval_separator separator between key and value of map. For default it is the '=>'
    //! \param first_bracket data before collection's elements (usual it is the parenthesis, square or curly bracker '(', '[', '{')
    //! \param last_bracket data after collection's elements (usual it is the parenthesis, square or curly bracker ')', ']', '}')
    SET_TEMPLATE
    void print( const Container<T, Compare, Alloc>& collection
              , const std::string& elem_separator   = default_elem_separator
              , const std::string& first_bracket    = default_first_bracket
              , const std::string& last_bracket     = default_last_bracket
              , std::ostream& os = std::cout
              , bool needEndl = true
            )
    {
        typename Container<T, Compare, Alloc>::const_iterator it = collection.begin();
        BUILD_CONTENT
        COMPILE_CONTENT
    }


    //! Prints collections like std:unordered_set<Key, Hash, Pred, Alloc> as in Python
    //! \param collection which should be printed
    //! \param elem_separator the separator which will be inserted between elements of collection
    //! \param keyval_separator separator between key and value of map. For default it is the '=>'
    //! \param first_bracket data before collection's elements (usual it is the parenthesis, square or curly bracker '(', '[', '{')
    //! \param last_bracket data after collection's elements (usual it is the parenthesis, square or curly bracker ')', ']', '}')
    USET_TEMPLATE
    void print( const Container<Key, Hash, Pred, Alloc>& collection
              , const std::string& elem_separator   = default_elem_separator
              , const std::string& first_bracket    = default_first_bracket
              , const std::string& last_bracket     = default_last_bracket
              , std::ostream& os = std::cout
              , bool needEndl = true
            )
    {
        typename Container<Key, Hash, Pred, Alloc>::const_iterator it = collection.begin();
        BUILD_CONTENT
        COMPILE_CONTENT
    }

    //! Prints collections like std:map<T, U> as in Python
    //! supports generic objects of std: map, multimap
	//! \param collection which should be printed
	//! \param elem_separator the separator which will be inserted between elements of collection
	//! \param keyval_separator separator between key and value of map. For default it is the '=>'
	//! \param first_bracket data before collection's elements (usual it is the parenthesis, square or curly bracker '(', '[', '{')
	//! \param last_bracket data after collection's elements (usual it is the parenthesis, square or curly bracker ')', ']', '}')
    MAP_TEMPLATE
    void print(   const Container<Key, Value>& collection
                , const std::string& elem_separator   = default_elem_separator
                , const std::string& keyval_separator = default_keyval_separator
                , const std::string& first_bracket    = default_first_bracket
                , const std::string& last_bracket     = default_last_bracket
                , std::ostream& os = std::cout
                , bool needEndl = true
        )
	{
        typename Container<Key, Value>::const_iterator it = collection.begin();
		BUILD_MAP_CONTENT
        COMPILE_CONTENT
	}

    //! Prints classes like std:unordered_map as in Python
    //! \param collection which should be printed
    //! \param elem_separator the separator which will be inserted between elements of collection
    //! \param keyval_separator separator between key and value of map. For default it is the '=>'
    //! \param first_bracket data before collection's elements (usual it is the parenthesis, square or curly bracker '(', '[', '{')
    //! \param last_bracket data after collection's elements (usual it is the parenthesis, square or curly bracker ')', ']', '}')
    UMAP_TEMPLATE
    void print(   const Container<Key, Value, Hash, Pred, Alloc>& collection
                , const std::string& elem_separator   = default_elem_separator
                , const std::string& keyval_separator = default_keyval_separator
                , const std::string& first_bracket    = default_first_bracket
                , const std::string& last_bracket     = default_last_bracket
                , std::ostream& os = std::cout
                , bool needEndl = true
        )
    {
        typename Container<Key, Value, Hash, Pred, Alloc>::const_iterator it = collection.begin();
        BUILD_MAP_CONTENT
        COMPILE_CONTENT
    }

    //! Prints collections like std:array<T, Size> as in Python
	//! \param collection which should be printed
	//! \param elem_separator the separator which will be inserted between elements of collection
	//! \param keyval_separator separator between key and value of map. For default it is the '=>'
	//! \param first_bracket data before collection's elements (usual it is the parenthesis, square or curly bracker '(', '[', '{')
	//! \param last_bracket data after collection's elements (usual it is the parenthesis, square or curly bracker ')', ']', '}')
    ARRAY_TEMPLATE
    void print(   const Array<Type, Size>& collection
                , const std::string& elem_separator   = default_elem_separator
                , const std::string& first_bracket    = default_first_bracket
                , const std::string& last_bracket     = default_last_bracket
                , std::ostream& os = std::cout
                , bool needEndl = true
            )
    {
        typename Array<Type, Size>::const_iterator it = collection.begin();
        BUILD_CONTENT
        COMPILE_CONTENT
    }

	//! Removes all whitespaces before data in string.
	//! \param str string with data
	//! \return string without whitespaces in left part
    std::string ltrim(const std::string& str);

	//! Removes all whitespaces after data in string
	//! \param str string with data
	//! \return string without whitespaces in right part
    std::string rtrim(const std::string& str);

	//! Removes all whitespaces before and after data in string
	//! \param str string with data
	//! \return string without whitespaces before and after data in string
    std::string trim(const std::string& str);



    ////////////////////////////////////////////////////////////
    ////////////////////////ostream logic//////////////////////
    /// Should be specified for concrete containers
    /// because of another types can be suitable
    /// for templates, for example templates break
    /// the code like this "cout << string("hello") << endl;"
    ////////////////////////////////////////////////////////////



#define PROCESS_VALUE_COLLECTION(os, collection)                            \
    print(  collection,                                                     \
            default_elem_separator,                                         \
            default_first_bracket,                                          \
            default_last_bracket,                                           \
            os,                                                             \
            false                                                           \
    );                                                                      \

#define PROCESS_KEY_VALUE_COLLECTION(os, collection)                        \
    print(  collection,                                                     \
            default_elem_separator,                                         \
            default_keyval_separator,                                       \
            default_first_bracket,                                          \
            default_last_bracket,                                           \
            os,                                                             \
            false                                                           \
    );                                                                      \

    ///< specialization for vector
    template<class T>
    std::ostream& operator<<(std::ostream& os, const std::vector<T>& collection)
    {
        PROCESS_VALUE_COLLECTION(os, collection)
        return os;
    }

    ///< specialization for deque
    template<class T>
    std::ostream& operator<<(std::ostream& os, const std::deque<T>& collection)
    {
        PROCESS_VALUE_COLLECTION(os, collection)
        return os;
    }

    ///< specialization for list
    template<class T>
    std::ostream& operator<<(std::ostream& os, const std::list<T>& collection)
    {
        PROCESS_VALUE_COLLECTION(os, collection)
        return os;
    }

    ///< specialization for set
    template<class T>
    std::ostream& operator<<(std::ostream& os, const std::set<T>& collection)
    {
        PROCESS_VALUE_COLLECTION(os, collection)
        return os;
    }

    ///< specialization for multiset
    template<class T>
    std::ostream& operator<<(std::ostream& os, const std::multiset<T>& collection)
    {
        PROCESS_VALUE_COLLECTION(os, collection)
        return os;
    }

#ifdef MODERN_CPP_AVAILABLE
    ///< specialization for unordered_map
    template<class T>
    std::ostream& operator<<(std::ostream& os, const std::unordered_set<T>& collection)
    {
        PROCESS_VALUE_COLLECTION(os, collection)
        return os;
    }

    ///< specialization for forward_list
    template<class T>
    std::ostream& operator<<(std::ostream& os, const std::forward_list<T>& collection)
    {
        PROCESS_VALUE_COLLECTION(os, collection)
        return os;
    }

    ///< specialization for array
    template<class T, std::size_t N>
    std::ostream& operator<<(std::ostream& os, const std::array<T, N>& collection)
    {
        PROCESS_VALUE_COLLECTION(os, collection)
        return os;
    }
#endif

    ///< specialization for map, multimap
    MAP_TEMPLATE
    std::ostream& operator<<(std::ostream& os, const Container<Key, Value>& collection)
    {
        PROCESS_KEY_VALUE_COLLECTION(os, collection)
        return os;
    }

    ///< specialization for unordered_map
    UMAP_TEMPLATE
    std::ostream& operator<<(std::ostream& os, const Container<Key, Value, Hash, Pred, Alloc>& collection)
    {
        PROCESS_KEY_VALUE_COLLECTION(os, collection)
        return os;
    }
}
