/*! \file   	wire.hpp
*	\brief		The wrapper under std::string with wide functionality.
*
*  \author 		Skident
*  \date   		27.10.2016
*  \copyright	Skident Inc.
*/


#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

namespace eos
{
    class wire
    {
    private:
        std::string m_container;

        template<class T>
        T convert ()
        {
            std::stringstream ss;
            T result;
            ss << m_container;
            ss >> result;
            return result;
        }

    public:
        // iterators
        typedef std::string::iterator iterator;
        typedef std::string::const_iterator const_iterator;
        typedef std::string::reverse_iterator reverser_iterator;
        typedef std::string::const_reverse_iterator const_reverse_iterator;
        
        iterator begin();
        iterator end();
        const_iterator cbegin();
        const_iterator cend();
        reverser_iterator rbegin();
        reverser_iterator rend();
        const_reverse_iterator crbegin();
        const_reverse_iterator crend();
        
        
        // constructors
        wire();
        wire(const std::string& value);
        wire(const char* value);
        wire(const char value);

        template<class T>
        wire(const T& value)
        {
            std::stringstream ss;
            ss << value;
            m_container = ss.str();
        }

        wire(const wire& rhs);
        wire& operator=(const wire& rhs);
        wire& operator=(const std::string& rhs);

        ~wire();

        
        // operators
        operator std::string();
        operator std::string() const;

        template<class T>
        operator T()
        {
            return convert<T>();
        }

        template<class T>
        operator T() const
        {
            return convert<T>();
        }

        operator char();
        operator char() const;

        template<class T>
        wire& operator+(const T& value)
        {
            std::string res = wire(value);
            m_container += res;
            return *this;
        }

        wire& operator+(const char* value);

        wire& operator+(const char value);

        wire& operator+=(const wire& value);

        wire operator[](std::size_t idx);

        std::ostream& operator<<(std::ostream& os);

        template<class T>
        wire& operator<<(const T& value)
        {
            std::string res = value;
            m_container += res;
            return *this;
        }


        friend std::ostream& operator<<(std::ostream& os, wire rhs);



        // Useful methods
        wire& trim();
        wire& rtrim();
        wire& ltrim();


        wire& substr(int from, int to);
        wire& remove(const wire& substr);
        wire& removeAll(const wire& substr);
        
        std::vector<wire> split(void) const;
        std::vector<wire> split(const wire& separator) const;

        std::size_t length() const;
        bool empty() const;
        bool contains(const wire& substr) const;
		std::string str() const
		{
			return m_container;
		}

        wire& append(const wire& tail)
        {
            std::string tmp = tail.str();
            m_container.append(tmp);
            return *this;
        }
        
        wire& reverse(void);

    };
}
