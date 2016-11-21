//
//  optional.hpp
//  eos
//
//  Created by Skident on 11/11/16.
//
//

#pragma once

#include <cstddef>
#include <iostream>

namespace eos
{
    template <class T>
    class optional
    {
    public:
        //! Default constructor
        optional()
        {
            
        }
        
        
        //! Constructor from template value
        optional(const T& value)
            : m_value(value)
            , m_wasSet(true)
        {
            
        }
        
        
        //! Store new value into optional
        void store(const T& value)
        {
            m_value = value;
            m_wasSet = true;
        }
        
        
        //! Reset current value in optional
        void reset()
        {
            m_wasSet = false;
        }
        
        
        //////////////////////
        // operators
        //////////////////////
        
        //! cast to bool
        operator bool() const
        {
            return m_wasSet;
        }
        
        
        //! cast to stored value type
        operator T() const
        {
            return m_value;
        }
        
        
        //! Check is the optional contains some value
        bool operator!() const
        {
            return !m_wasSet;
        }
        
        
        //! Comparison with nullptr
        bool operator==(std::nullptr_t nullpt) const
        {
            return !m_wasSet;
        }
        
        
        //! Not equal nullptr
        //! \return true - contains some value, false - otherwise
        bool operator!=(std::nullptr_t nullpt) const
        {
            return m_wasSet;
        }
        
        
        //! Comparison with another value of stored type
        //! \return true - equal, false - not equal
        bool operator==(const T& value) const
        {
            if (!m_wasSet)
                return false;
            
            return (m_value == value);
        }
        
        
        //! Not equal comparison
        //! \return true - not equal, false - equal
        bool operator!=(const T& value) const
        {
            return !(*this == value);
        }
        
        
        //! Comarison with another optional with the same type of content
        //! \return true - equal, false - not equal
        bool operator==(const optional<T>& rhs) const
        {
            if (!m_wasSet || !rhs.m_wasSet)
                return false;
            
            return (m_value == rhs.m_value);
        }
        
        
        //! Not equal comparison between two optionals
        //! \return true - not equal, false - equal
        bool operator!=(const optional<T>& rhs) const
        {
            return !(*this == rhs);
        }
        
        
        //! Print content of optional into ostream
        //! \param os reference to ostream
        //! \return reference to ostream
        std::ostream& operator<<(std::ostream& os) const
        {
            if (m_wasSet)
                os << m_value;
            return os;
        }
        
        
        //! Friend ostream operator
        //! \param os reference to ostream
        //! \param rhs optional object
        //! \return reference to ostream
        template<class U>
        friend std::ostream& operator<<(std::ostream& os, const optional<U>& rhs);
        
        
        //! Comparison between value with type stored in optional and optional
        //! \param lhs type stored in optional
        //! \param rhs optional object
        //! \return true - lhs and data stored in optional are equal, false - not equal
        template<class U>
        friend bool operator==(const U& lhs, const optional<U>& rhs);

        
        //! Checks for not equality of plain type and optional with this type
        //! \param lhs value with type stored in optional
        //! \param rhs optional
        //! \return true - not equal, false - equal
        template<class U>
        friend bool operator!=(const U& lhs, const optional<U>& rhs);

        
        //! Comparison of nullptr and optional
        template<class U>
        friend bool operator==(std::nullptr_t nullpt, const optional<U>& rhs);

        
        //! Comparison for not equality with nullptr and optional
        template<class U>
        friend bool operator!=(std::nullptr_t nullpt, const optional<U>& rhs);

        
    private:
        T m_value;              ///< generic value
        bool m_wasSet = false;  ///< flag for check is optional empty or not
    };
    
    
    /////////////////////////
    // friends implementation
    /////////////////////////
    template<class U>
    std::ostream& operator<<(std::ostream& os, const optional<U>& rhs)
    {
        if (rhs.m_wasSet)
            os << rhs.m_value;
        return os;
    }
    
    template<class U>
    bool operator==(const U& lhs, const optional<U>& rhs)
    {
        return rhs == lhs;
    }

    template<class U>
    bool operator!=(const U& lhs, const optional<U>& rhs)
    {
        return rhs != lhs;
    }
    
    template<class U>
    bool operator==(std::nullptr_t nullpt, const optional<U>& rhs)
    {
        return rhs == nullpt;
    }
    
    template<class U>
    bool operator!=(std::nullptr_t nullpt, const optional<U>& rhs)
    {
        return rhs != nullpt;
    }


}
