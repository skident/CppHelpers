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
        
        
        static const std::size_t npos = -1;

        
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
        
        wire multiply(std::size_t times) const;
        
        //! get sub-wire from current wire
        //! \param from position from which new wire should be started
        //! \param to the index of the end of the new sub-wire
        wire substr(int from, int to = npos) const;
        
        //! remove all chuks
        //! \param chunk the substring which should be removed
        wire& remove(const wire& chunk);
        
        //! Replace all found substrings by new substring.
        wire& replace(const wire& substr, const wire& newsubstr);
        
        wire masking(wire mask, int unmaskedLeft, int unmaskedRight = npos) const;
        
        wire padding(wire mask, int leftCount, int rightCount = npos) const;
        
        std::vector<wire> split(void) const;
        std::vector<wire> split(const wire& separator) const;

        std::size_t length() const;
        bool empty() const;
        bool contains(const wire& substr) const;
        std::string str() const;

        wire& append(const wire& tail);
        wire& reverse(void);

    };
}
