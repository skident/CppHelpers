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

        wire& operator+(const wire& value)
        {
            std::string res = value;
            m_container += res;
            return *this;
        }

        wire& operator+(const char* value)
        {
            std::string res = wire(value);
            m_container += res;
            return *this;
        }

        wire& operator+(const char value)
        {
            std::string res = wire(value);
            m_container += res;
            return *this;
        }


        wire& operator+=(const wire& value)
        {
            std::string res = value;
            m_container += res;
            return *this;
        }

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
        std::vector<wire> split(const wire& separator) const;

        std::size_t length() const;
        bool empty() const;
        bool contains(const wire& substr) const;

        wire& append(const wire& tail)
        {
            std::string tmp = tail;
            m_container.append(tmp);
            return *this;
        }


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
    };
}
