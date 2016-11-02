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
#include <stdexcept>

#define forever while (true)

namespace eos
{
    class wire
    {
    public:
	    static const std::size_t npos = -1;  // TODO: think is this constant really needed 
		friend std::ostream& operator<<(std::ostream& os, wire rhs);

        //************** iterators *****************//
        typedef std::string::iterator				iterator;
        typedef std::string::const_iterator			const_iterator;
        typedef std::string::reverse_iterator		reverser_iterator;
        typedef std::string::const_reverse_iterator const_reverse_iterator;
        
        iterator begin()
        {
			return m_container.begin();
        }
        iterator end()
        {
			return m_container.end();
        }
    	const_iterator begin() const noexcept
		{
			return m_container.begin();
		}
		const_iterator end() const noexcept
		{
			return m_container.end();
		}
        const_iterator cbegin() const noexcept
		{
			return m_container.cbegin();
		}
        const_iterator cend() const noexcept
		{
			return m_container.cend();
		}
        reverser_iterator rbegin()
        {
			return m_container.rbegin();
        }
        reverser_iterator rend()
        {
			return m_container.rend();
        }
        const_reverse_iterator crbegin() const noexcept
		{
			return m_container.crbegin();
		}
        const_reverse_iterator crend() const noexcept
		{
			return m_container.crend();
		}
		//************** iterators end *****************//
                


		//************** constructors *****************//
		//! Destructor
    	~wire()
        {	       
        }

		//! Default constructor
        wire()
        {	        
        }

		//! Constructor from std::string
        wire(const std::string& data)
			:m_container(data)
        {	        
        }

		//! Constructor from C-style string
        wire(const char* value)
        {
			m_container.assign(value);
        }

		//! Constructor from char 
        wire(const char value)
        {
			m_container.assign(1, value);
        }

		//! Generic constructor for other types 
		//! like int, double, long ...
        template<class T>
        wire(const T& value)
        {
            std::stringstream ss;
            ss << value;
            m_container = ss.str();
        }

		//! Copy constructor
        wire(const wire& rhs)
        {
			m_container = rhs.m_container;
        }

		//! Assignment operator
        wire& operator=(const wire& rhs)
		{
			if (this != &rhs)
				m_container = rhs.m_container;
			return *this;
		}

		//! Assignment operator for string
        wire& operator=(const std::string& rhs)
		{
			m_container = rhs;
			return *this;
		}

		//! Assignment operator for string
		template<class T>
		wire& operator=(const T& rhs)
		{
			m_container = wire(rhs).str();
			return *this;
		}

		// TODO: move constructor and operator
		//************** constructors end *****************//
        


		//************** operators and so on *****************//
		//! Cast operator to string
        operator std::string()
        {
			return m_container;
        }
		
    	//! Cast operator to const string
        operator std::string() const
        {
			return m_container;
        }

		//! Generic cast operator for primitive types
        template<class T>
        operator T()
        {
            return convert<T>();
        }

		//! Generic cast operator for primitive const types
        template<class T>
        operator T() const
        {
            return convert<T>();
        }

		//! Cast operator to char
		//! Notice: return space if data is empty
        operator char()
		{
			return getFirstElement();
		}
		
		//! Cast operator to const char
		//! Notice: return space if data is empty
        operator char() const
		{
			return getFirstElement();
		}

		//! Operator + for concatenate wire and generic value
        template<class T>
        wire& operator+(const T& value)
        {
            std::string res = wire(value);
            m_container += res;
            return *this;
        }

		//! Operator + for C-style strings
        wire& operator+(const char* value)
		{
			m_container += std::string(value);
			return *this;
		}

		//! Operator + for char values
        wire& operator+(const char value)
		{
			m_container.append(1, value);
			return *this;
		}

		//! Operator += for wire
        wire& operator+=(const wire& value)
		{
			m_container += value.str();
			return *this;
		}
        
		//! Access to the element by []
		//! \return wire object
        wire operator[](const std::size_t& idx)
        {
			if (idx >= m_container.length())
				throw std::out_of_range("Too big index");

			wire result(m_container.at(idx));
			return result;
        }

		//! Overloaded operator for appending wire into stream
        std::ostream& operator<<(std::ostream& os) const
		{
			os << m_container;
			return os;
		}

		//! Append generic value into wire like into stream
        template<class T>
        wire& operator<<(const T& value)
        {
			std::stringstream ss;
			ss << value;
			m_container += ss.str();
        	return *this;
        }

		//! Equal operator
		bool operator==(const wire& rhs) const
		{
			return (m_container == rhs.m_container);
		}

		//! Not Equal operator
		bool operator!=(const wire& rhs) const
		{
			return (m_container != rhs.m_container);
		}


		//! Not Equal operator
		template<class T>
		bool operator!=(const T& rhs) const
		{
			return (m_container != wire(rhs).str());
		}

		//! Less operator
		bool operator<(const wire& rhs) const
		{
			return (m_container < rhs.m_container);
		}

		//! \return string representation of self
		std::string str() const
		{
			return m_container;
		}
		//************** operators end *****************//



		//************** std::strng methods **************//
		//! \return length of wire
		std::size_t length() const
		{
			return m_container.length();
		}

		//! \return true - if wire is empty, false - not empty
		bool empty() const
		{
			return m_container.empty();
		}

		//! get sub-wire from current wire
		//! \param from position from which new wire should be started
		//! \param to the index of the end of the new sub-wire
		wire substr(std::size_t from, std::size_t to = npos) const
        {
			auto res = m_container.substr(from, to);
			return wire(res);
        }

		//! Wrapper for std::string find method
		//! \return position of found substring or npos if not found
		template<class T>
		bool find(const T& value) const
        {
			auto pos = m_container.find(wire(value).str());
			return pos;
        }
		//************** std::strng methods end **************//



		//************** Useful methods **************//
		//! Removes white-spaces before and after data.
		//! \return the reference to itself 
    	wire& trim();

		//! Removes white-spaces after data.
		//! \return the reference to itself 
        wire& rtrim();

		//! Removes white-spaces before data.
		//! \return the reference to itself 
		//! \return the reference to itself 
        wire& ltrim();
        
		//! Duplicates current content N times
		//! \param times how many times data will be duplicate
		//! \return the new instance of wire.
        wire multiply(std::size_t times) const;
        
        //! Removes all chuks
        //! \param chunk the substring which should be removed
		//! \return the reference to itself 
        wire& remove(const wire& chunk);
        
        //! Replaces all found substrings by new substring.
		//! \return the reference to itself 
        wire& replace(const wire& substr, const wire& newsubstr);
        
		//! Masks data in wire.
		//! \param mask wire object which will be inserted instead of each symbol in old data
		//! \param unmaskedLeft count of symbols which will be unmasked from left side
		//! \param unmaskedRight count of symbls which will be unmasked from right side
		//! \return the new instance of wire.
        wire masking(wire mask, std::size_t unmaskedLeft, std::size_t unmaskedRight = npos) const;
        
		//! Adds padding before and after original data.
		//! \param mask wire object which will be added to data
		//! \param leftCount how many symbols must be padded before data
		//! \param rightCount how many symbols must be padded after data
		//! \return the new instance of wire.
        wire padding(wire mask, std::size_t leftCount, std::size_t rightCount = npos) const;
        
		//! Splits wire object onto vector of wires.
		//! Every symbol will be added into vector
        std::vector<wire> split(void) const;

		//! Splits wire object onto vector of wires.
		//! \param separator the separator between chunks
        std::vector<wire> split(const wire& separator) const;

		//! \return true if substr in wire
		bool contains(const wire& substr) const;

		//! Appends data into the end of self
		//! \return the new instance of wire.
    	wire& append(const wire& tail);

		//! Reverse itself.
		//! \return the new instance of wire.
        wire& reverse(void);


	private:
		std::string m_container;

		template<class T>
		T convert()
		{
			std::stringstream ss;
			T result;
			ss << m_container;
			ss >> result;
			return result;
		}

		char getFirstElement() const
		{
			if (m_container.empty())
				return ' ';
			return m_container.at(0);
		}
    };
}
