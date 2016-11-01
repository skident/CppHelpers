/*! \file   	wire.cpp
*	\brief		The wrapper under string with wide functionality.
*
*  \author 		Skident
*  \date   		27.10.2016
*  \copyright	Skident Inc.
*/


#include "eos/types/wire.hpp"
#include <cctype>

using namespace std;


namespace eos
{
	ostream& operator<<(ostream& os, wire rhs)
	{
		os << rhs.m_container;
		return os;
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
		string result;
		string str = m_container;
		size_t len = str.length();
		auto i = static_cast<int>(len - 1);
		for (; i >= 0; i--)
		{
			if (isspace(str[i]) == 0)
				break;
		}

		result = str.substr(0, i + 1);
		m_container = result;

		return *this;
	}

	wire& wire::ltrim()
	{
		string result;
		string str = m_container;
		size_t len = str.length();
		size_t i = 0;
		for (; i < len; i++)
		{
			if (isspace(str[i]) == 0)
				break;
		}

		if (i < len)
			result = str.substr(i);
		m_container = result;

		return *this;
	}

	bool wire::contains(const wire& substr) const
	{
		string primitiveSubstr = substr.str();
		bool found = m_container.find(primitiveSubstr) != string::npos; //trick for debugging
		return found;
	}


	wire wire::multiply(size_t times) const
	{
		size_t newLength = times * m_container.length();
		string result;
		result.reserve(newLength);

		for (size_t i = 0; i < times; i++)
			result += m_container;

		return wire(result);
	}

	wire& wire::remove(const wire& chunk)
	{
		auto workCopy = m_container;
		auto primitiveSubstr = chunk.str();
		
		forever
		{
			auto pos = workCopy.find(primitiveSubstr);
			if (pos == string::npos)
				break;

			// TODO: it can be improved
			workCopy = workCopy.substr(0, pos) + workCopy.substr(pos + primitiveSubstr.length());
		}
		m_container = workCopy;
		return *this;
	}

	//! Replace all found substrings by new substring.
	wire& wire::replace(const wire& substr, const wire& newsubstr)
	{
		auto workCopy = m_container;
		auto primitiveSubstr = substr.str();
		
		forever
		{
			auto pos = workCopy.find(primitiveSubstr);
			if (pos == string::npos)
				break;

			// TODO: it can be improved
			workCopy = workCopy.substr(0, pos) + newsubstr.str() + workCopy.substr(pos + primitiveSubstr.length());
		}
		m_container = workCopy;
		return *this;

	}

	wire wire::masking(wire mask, size_t unmaskedLeft, size_t unmaskedRight) const
	{
		if (unmaskedRight == npos)
			unmaskedRight = unmaskedLeft;

		// for avoid too huge digits which will give small digit in sum
		const auto len = length();
		if (unmaskedLeft >= len || unmaskedRight >= len)
		{
			return *this;
		}


		auto unmaskedPart = unmaskedLeft + unmaskedRight;
		if (unmaskedPart < length())
		{
			auto remains = length() - unmaskedPart;
			auto result = substr(0, unmaskedLeft) 
						+ mask.multiply(remains)  
						+ substr(m_container.length() - unmaskedRight);
			
			return result;
		}

		return *this;
	}

	wire wire::padding(wire mask, size_t leftCount, size_t rightCount) const
	{
		if (rightCount == npos)
			rightCount = leftCount;
		auto result = mask.multiply(leftCount) + (*this) + mask.multiply(rightCount);
		return result;
	}


	vector<wire> wire::split(void) const
	{
		vector<wire> chunks;
		for (size_t i = 0; i < m_container.length(); i++)
		{
			chunks.emplace_back(m_container[i]);
		}
		return chunks;
	}

	vector<wire> wire::split(const wire& separator) const
	{
		vector<wire> chunks;
		auto tmp = m_container;
		auto primitiveSeparator = separator.str();
		
		forever
		{
			auto pos = tmp.find(primitiveSeparator);
			if (pos == string::npos)
			{
				// append the last chunk
				if (!tmp.empty())
					chunks.emplace_back(tmp);
				break;
			}				

			auto chunk = tmp.substr(0, pos);
			if (!chunk.empty())
				chunks.emplace_back(tmp.substr(0, pos));

			tmp = tmp.substr(pos + separator.length());
		}

		return chunks;
	}

	wire& wire::append(const wire& tail)
	{
		m_container.append(tail.str());
		return *this;
	}

	wire& wire::reverse(void)
	{
		auto halfSize = m_container.size() / 2;
		char tmp;
		for (size_t i = 0, j = m_container.size() - 1; i < halfSize; i++, j--)
		{
			tmp = m_container[i];
			m_container[i] = m_container[j];
			m_container[j] = tmp;
		}
		return *this;
	}
}
    
