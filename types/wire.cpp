#include "wire.hpp"
#include <exception>


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
    string primitiveSubstr = substr;
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
    string primitiveSubstr = substr;
    auto pos = m_container.find(primitiveSubstr);
    if (pos != string::npos)
        m_container = m_container.substr(0, pos) + m_container.substr(pos+primitiveSubstr.length());

    return *this;
}

wire& wire::removeAll(const wire& substr)
{
    string workCopy = m_container;
    string primitiveSubstr = substr;
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

std::vector<wire> wire::split(const wire& separator) const
{
    vector<wire> chunks;
    string tmp = m_container;
    string primitiveSeparator = separator;
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


/////////////////////
// Iterators

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

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
/// Test code!!! Shoud be moved to its own file ///

#include <sstream>
#include <print.hpp>

int main()
{
    using namespace eos;

    // test casts from string <-> String
    {
    string res = wire("Implicit cast test");
    wire res2 = res;
    cout << "string vaue: '" << res << "', String value: '" << res2 << "'" << endl;
    }

    // test working with streams
    {
    wire str("Work with streams str");
    stringstream ss;

    ss << str;
    cout << str << endl;
    cout << ss.str() << endl; // the remain part
    }


    // test trim(s)
    {
    wire test("  123   ");
    cout << test << endl;
    // trim changes the real object
    cout << "'" << wire(test).ltrim() << "'" << endl;
    cout << "'" << wire(test).rtrim() << "'" << endl;
    cout << "'" << wire(test).trim() << "'" << endl;
    }


    // test substr
    {
        wire str("123");
        cout << str.substr(1,2) << endl;
    }

    // test remove and removeAll
    {
        wire digits(1234554321231);
        digits.remove(4);
        cout << "digits after remove 4: " << digits << endl;

        digits.removeAll(23);
        cout << "digits after remove all 23: " << digits << endl;

        wire word("abcabab");
        cout << word.removeAll("ab") << endl;
    }


    // Test split string on chunks
    {
        wire str(1234512367123);
        cout << str.split(12) << endl;
    }


    // Test constructor with char
    {
        wire charObj('c');
        cout << charObj << endl;
    }

    // Test contains method
    {
        wire res(33344511);
        cout << "Does contain digit 3? " << res.contains(3) << endl;
        cout << "Does contain digit 0? " << res.contains(0) << endl;
    }

    // implicit casts
    {
        int digit = wire(123);
        short shortDigit = wire(321);
        const long long bigData = wire(12345212345676543);
        const char symbol = wire("qwerty");
        char symbol2 = wire();

        cout << digit << endl;
        cout << shortDigit << endl;
        cout << bigData << endl;
        cout << symbol << endl;
        cout << "'" << symbol2 << "'" << endl;
    }

    // concatenate test
    {
        wire str, str2, str3;
        const int n = 10;

        str3 += wire(n) + "112" + 'c';

        for (int i = 0 ; i < 10; i++)
        {
            str = str + i;
            str2 += i;
        }



        cout << str << endl;
        cout << str2 << endl;
        cout << str3 << endl;
    }


    // Tests with iterators
    {
        wire str("qwerty");
        for (const auto& symbol : str)
            cout << symbol << " : ";
        cout << endl;
    }

}
