/*! \file   	range.h
 *	\brief		Rnages container based on std::multimap.
 *			
 *	This class provides a few simple methods for work.
 *  It uses for fast searching needed value in ranges.
 *
 *  \author 	Skident
 *  \date   	06.10.2016
 *  \copyright  Skident inc.
 */

#include <map>
#include <eos/io/print.hpp>
#include <iostream>

namespace eos
{
	template <typename T>
	class range
	{
	public:
		typedef std::pair<T, T> MinMax;

		const static bool strict_bound = true;
		const static bool not_strict_bound = false;

		//! Default constructor
		range()
		{
			
		}

		//! Copy constructor
		range(const range& rhs)
		{
			if (this != &rhs)
				m_storage = rhs.m_storage;
		}

		//! Copy constructor
		range& operator=(const range& rhs)
		{
			m_storage = rhs.m_storage;
			return *this;
		}

		//! Destructor
		virtual ~range() 
		{
			
		}

		//! Add new range into container
		//! \param range min and max values for range
		void insert(MinMax range)
		{
			m_storage.insert(range);
		}

		//! Find the value in range
		//! \param value searched value
		//! \param strictLowerLimit if true then value should be greater than lower limit of range, false - they can be equal
		//! \param strictUpperLimit if true then value should be lower than upper limit of range, false - they can be equal
		//! \return true if some range containes the value, false - otherwise
		bool find(T value, bool strictLowerLimit = strict_bound, bool strictUpperLimit = not_strict_bound) const
		{
			// storage is empty. Nothing to do here.
			if (m_storage.empty())
				return false;

			// try to find the nearest key
			auto it = m_storage.lower_bound(value); 

			// out of bound (previous range can be the needed one)
			if (it == m_storage.end())
				--it;

			// check is value in current range
			bool bInRange = isInRange(*it, value, strictLowerLimit, strictUpperLimit);
			if (bInRange)
				return true;

			// it was the first element in storage
			if (it == m_storage.begin())
				return false;

			// try to check previous range
			--it;
			bInRange = isInRange(*it, value, strictLowerLimit, strictUpperLimit);
			return bInRange;
		}

		//! clear the storage with ranges
		void clear()
		{
			m_storage.clear();
		}

		//! \return true if container is empty, false - otherwise
		bool empty() const
		{
			return m_storage.empty();
		}

		//! print all ranges
		void print() const
		{
			for (auto it : m_storage)
				std::cout << it.first << " : " << it.second << std::endl;
		}

        template<class U>
		friend std::ostream& operator<<(std::ostream& os, const range<U>& obj);
		

		bool operator==(const range& rhs) const
		{
			return (m_storage == rhs.m_storage);
		}

		bool operator!=(const range& rhs) const
		{
			return (m_storage != rhs.m_storage);
		}

	private:
		std::multimap<T, T> m_storage;

		static bool isInRange(const MinMax& range, const T& value, bool strictLowerLimit, bool strictUpperLimit)
		{
			if (strictLowerLimit && range.first == value)
				return true;

			if (strictUpperLimit && range.second == value)
				return true;

			if (range.first < value && value < range.second)
				return true;
			return false;
		}
	};
    

    template <class U>
    std::ostream& operator<<(std::ostream& os, const range<U>& obj)
    {
    	os << obj.m_storage;
    	return os;
    }
};


