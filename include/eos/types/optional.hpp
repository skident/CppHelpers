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
        operator T()
        {
            return m_value;
        }
        
        bool operator!()
        {
            return !m_wasSet;
        }
        
        bool operator==(std::nullptr_t nullpt)
        {
            return !m_wasSet;
        }
        
        bool operator!=(std::nullptr_t nullpt)
        {
            return m_wasSet;
        }

        bool operator==(const T& value)
        {
            if (!m_wasSet)
                return false;
            
            return (m_value == value);
        }
        
        bool operator!=(const T& value)
        {
            return !(*this == value);
        }
        
        bool operator==(const optional<T>& rhs)
        {
            if (!m_wasSet || !rhs.m_wasSet)
                return false;
            
            return (m_value == rhs.m_value);
        }
        
        bool operator!=(const optional<T>& rhs)
        {
            return !(*this == rhs);
        }
        
        std::ostream& operator<<(std::ostream& os)
        {
            if (m_wasSet)
                os << m_value;
            return os;
        }
        
        template<class U>
        friend std::ostream& operator<<(std::ostream& os, const optional<U>& rhs);
        
    private:
        T m_value;
        bool m_wasSet = false;
    };
    
    
    template<class U>
    std::ostream& operator<<(std::ostream& os, const optional<U>& rhs)
    {
        if (rhs.m_wasSet)
            os << rhs.m_value;
        return os;
    }

}
