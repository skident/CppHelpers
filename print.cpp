#include "print.hpp"

namespace eos
{

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
        int i = static_cast<int>(len-1);
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
}

