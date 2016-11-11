//
//  optional.hpp
//  eos
//
//  Created by Skident on 11/11/16.
//
//

#pragma once

#include <cstddef>

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
        
    private:
        T m_value;
        bool m_wasSet = false;
    };
    

}
