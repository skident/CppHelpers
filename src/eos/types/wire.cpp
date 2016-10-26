#include "eos/types/wire.hpp"
#include <cctype>
#include <stdexcept>

using namespace std;


namespace eos
{


std::ostream& operator<<(std::ostream& os, wire rhs)
{
    os << rhs.m_container;
    return os;
}

wire::wire(void)
{

}

wire::wire(const std::string& data)
    : m_container(data)
{

}

wire::wire(const char* value)
{
    m_container.assign(value);
}

wire::wire(const char value)
{
    m_container.assign(1, value);
}

wire::~wire()
{

}

wire::wire(const wire& rhs)
{
    m_container = rhs.m_container;
}

wire& wire::operator=(const wire& rhs)
{
    if (this != &rhs)
        m_container = rhs.m_container;
    return *this;
}

wire& wire::operator=(const std::string& rhs)
{
    m_container = rhs;
    return *this;
}

std::ostream& wire::operator<<(std::ostream& os)
{
    os << m_container;
    return os;
}

wire& wire::operator+(const char* value)
{
    m_container += string(value);
    return *this;
}

wire& wire::operator+(const char value)
{
    m_container.append(1, value);
    return *this;
}


wire& wire::operator+=(const wire& value)
{
    m_container += value.str();
    return *this;
}
    
// return space if data is empty
wire::operator char()
{
    if (m_container.empty())
        return ' ';
    return m_container.at(0);
}

wire::operator char() const
{
    if (m_container.empty())
        return ' ';
    return m_container.at(0);
}

wire::operator std::string()
{
    return m_container;
}
wire::operator std::string() const
{
    return m_container;
}

wire wire::operator[](size_t idx)
{
    if (idx >= m_container.length())
        throw out_of_range("Too big index");

    wire result(m_container.at(idx));
    return result;
}



// Useful methods
wire& wire::trim()
{
    ltrim();
    rtrim();
    return *this;
}

wire& wire::rtrim()
{
    std::string result;
    string str = m_container;
    std::size_t len = str.length();
    int i = static_cast<int>(len-1);
    for ( ; i >= 0; i--)
    {
        if (std::isspace(str[i]) == 0)
            break;
    }

    result = str.substr(0, i+1);
    m_container = result;

    return *this;
}

wire& wire::ltrim()
{
    std::string result;
    string str = m_container;
    std::size_t len = str.length();
    std::size_t i = 0;
    for ( ; i < len; i++)
    {
        if (isspace(str[i]) == 0)
            break;
    }

    if (i < len)
        result = str.substr(i);
    m_container = result;

    return *this;
}


size_t wire::length() const
{
    return m_container.length();
}

bool wire::empty() const
{
    return m_container.empty();
}

bool wire::contains(const wire& substr) const
{
    string primitiveSubstr = substr.str();
    bool found = m_container.find(primitiveSubstr) != string::npos; //trick for debugging
    return found;
}

wire& wire::substr(int from, int to)
{
    m_container = m_container.substr(from, to);
    return *this;
}

wire& wire::remove(const wire& substr)
{
    string primitiveSubstr = substr.str();
    auto pos = m_container.find(primitiveSubstr);
    if (pos != string::npos)
        m_container = m_container.substr(0, pos) + m_container.substr(pos+primitiveSubstr.length());

    return *this;
}

wire& wire::removeAll(const wire& substr)
{
    string workCopy = m_container;
    string primitiveSubstr = substr.str();
    while(true)
    {
        auto pos = workCopy.find(primitiveSubstr);
        if (pos == string::npos)
            break;

        // TODO: it can be improved
        workCopy = workCopy.substr(0, pos) + workCopy.substr(pos+primitiveSubstr.length());
    }
    m_container = workCopy;
    return *this;
}

    
std::vector<wire> wire::split(void) const
{
    vector<wire> chunks;
    for (size_t i = 0; i < m_container.length(); i++)
    {
        chunks.emplace_back(m_container[i]);
    }
    return chunks;
}
    
std::vector<wire> wire::split(const wire& separator) const
{
    vector<wire> chunks;
    string tmp = m_container;
    string primitiveSeparator = separator.str();
    for(;;)
    {
        auto pos = tmp.find(primitiveSeparator);
        if (pos == string::npos)
            break;
        auto chunk = tmp.substr(0, pos);
        if (!chunk.empty())
            chunks.push_back(tmp.substr(0, pos));
        tmp = tmp.substr(pos+separator.length());
    }

    // append the last chunk
    if (!tmp.empty())
        chunks.push_back(tmp);

    return chunks;
}


wire& wire::reverse(void)
{
    auto halfSize = m_container.size()/2;
    char tmp;
    for (size_t i = 0, j = m_container.size()-1; i < halfSize; i++, j--)
    {
        tmp = m_container[i];
        m_container[i] = m_container[j];
        m_container[j] = tmp;
    }
    return *this;
}
    
    
/////////////////////
// Iterators
// Just return the iterators of std::string
    
wire::iterator wire::begin()
{
    return m_container.begin();
}

wire::iterator wire::end()
{
    return m_container.end();
}

wire::const_iterator wire::cbegin()
{
    return m_container.cbegin();
}

wire::const_iterator wire::cend()
{
    return m_container.cend();
}

wire::reverser_iterator wire::rbegin()
{
    return m_container.rbegin();
}

wire::reverser_iterator wire::rend()
{
    return m_container.rend();
}

wire::const_reverse_iterator wire::crbegin()
{
    return m_container.crbegin();
}

wire::const_reverse_iterator wire::crend()
{
    return m_container.crend();
}


}
