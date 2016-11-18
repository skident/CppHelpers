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
        optional()
        {
            
        }
        
        optional(const T& value)
            : m_value(value)
            , m_wasSet(true)
        {
            
        }
        
        void store(const T& value)
        {
            m_value = value;
            m_wasSet = true;
        }
        
        void reset()
        {
            m_wasSet = false;
        }
        
        
        //////////////////////
        // operators
        //////////////////////
        operator bool() const
        {
            return m_wasSet;
        }
        
        operator T() const
        {
            return m_value;
        }
        
        bool operator!() const
        {
            return !m_wasSet;
        }
        
        bool operator==(std::nullptr_t nullpt) const
        {
            return !m_wasSet;
        }
        
        bool operator!=(std::nullptr_t nullpt) const
        {
            return m_wasSet;
        }
        
        bool operator==(const T& value) const
        {
            if (!m_wasSet)
                return false;
            
            return (m_value == value);
        }
        
        bool operator!=(const T& value) const
        {
            return !(*this == value);
        }
        
        bool operator==(const optional<T>& rhs) const
        {
            if (!m_wasSet || !rhs.m_wasSet)
                return false;
            
            return (m_value == rhs.m_value);
        }
        
        bool operator!=(const optional<T>& rhs) const
        {
            return !(*this == rhs);
        }
        
        std::ostream& operator<<(std::ostream& os) const
        {
            if (m_wasSet)
                os << m_value;
            return os;
        }
        
        template<class U>
        friend std::ostream& operator<<(std::ostream& os, const optional<U>& rhs);
        
        template<class U>
        friend bool operator==(const U& lhs, const optional<U>& rhs);

        template<class U>
        friend bool operator!=(const U& lhs, const optional<U>& rhs);

        template<class U>
        friend bool operator==(std::nullptr_t nullpt, const optional<U>& rhs);

        template<class U>
        friend bool operator!=(std::nullptr_t nullpt, const optional<U>& rhs);

        
    private:
        T m_value;
        bool m_wasSet = false;
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
