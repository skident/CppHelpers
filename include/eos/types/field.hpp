//
//  limitation.hpp
//  eos
//
//  Created by Skident on 11/29/16.
//
//

#pragma once

#include <cstddef>
#include <functional>
#include <vector>
#include <algorithm>
#include <iterator>
#include <exception>

#include "eos/types/optional.hpp"
#include "eos/types/wire.hpp"

namespace eos
{

template <class T>
class field
{
public:
    typedef std::function<bool(const T& value)> Validator;
    typedef std::vector<Validator> Validators;
    
    
    field& setValueLimits(const T& lower, const T& upper)
    {
        m_valueLimits = std::make_pair(lower, upper);
        
        return *this;
    }
    
    field& setLengthLimits(const std::size_t& minLength, const std::size_t& maxLength)
    {
        m_lengthLimits = std::make_pair(minLength, maxLength);

        return *this;
    }
    
    field& setValidator(const Validator& validator)
    {
        m_validators.emplace_back(validator);
        
        return *this;
    }
    
    field& setValue(const T& value)
    {
        validate(value);
        m_value = value;
        
        return *this;
    }
    
    T getValue() const
    {
        return m_value;
    }
    
    field& setValidator(const Validators& validators)
    {
        std::copy(validators.begin(), validators.end(), back_inserter(m_validators));
        
        return *this;
    }
    
    
    // TODO: throw own exception
    void validate(const T& value)
    {
        checkValueLimits(value);
        checkLengthLimits(value);
        
        for (const auto& validator : m_validators)
        {
            bool isValid = validator(value);
            if (!isValid)
                throw std::runtime_error("Validation failed");
        }
    }
    
    
private:
    eos::optional<std::pair<T, T>> m_valueLimits;
    eos::optional<std::pair<std::size_t, std::size_t>> m_lengthLimits;
    eos::optional<T> m_value;
    
    std::vector<Validator> m_validators;

    
    
    void checkValueLimits(const T& value)
    {
        if (!m_valueLimits)
            return;
        
        if (value < m_valueLimits.get().first)
            throw std::runtime_error("Value less than minimum");
        
        if (value > m_valueLimits.get().second)
            throw std::runtime_error("Value reater than maximum");
    }
    
    
    void checkLengthLimits(const T& value)
    {
        if (!m_lengthLimits)
            return;
        
        auto length = to_wire(value).length();
        if (length < m_lengthLimits.get().first)
            throw std::runtime_error("Value's length less than minimum length");
        
        if (length > m_lengthLimits.get().second)
            throw std::runtime_error("Value's length greater than maximum length");
    }

};

}
