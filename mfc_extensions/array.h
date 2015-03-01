#pragma once

#include "./traits.h"

namespace mfc
{
	namespace array
	{
		template <class T>
		struct Iterator
			: std::iterator<std::random_access_iterator_tag, typename mfc::traits::array_type<T>::type>
		{
		protected:
			pointer m_pData;

		public:
			// constructor
			Iterator() : m_pData(NULL) {}

			Iterator(const Iterator<T>& r) : m_pData(&(*r)) {}

			Iterator(pointer pData) : m_pData(pData) {}

			// operator
			Iterator& operator=(const Iterator<T>& r)
			{
				m_pData = &(*r);
				return *this;
			}
			Iterator& operator++()
			{
				++m_pData;
				return *this;
			}
			Iterator& operator--()
			{
				--m_pData;
				return *this;
			}
			Iterator operator++(int)
			{
				return Iterator(m_pData++);
			}
			Iterator operator--(int)
			{
				return Iterator(m_pData--);
			}
			Iterator operator+(const difference_type& n) const
			{
				return Iterator(m_pData + n);
			}
			Iterator& operator+=(const difference_type& n)
			{
				m_pData += n;
				return *this;
			}
			Iterator operator-(const difference_type& n) const
			{
				return Iterator(pointer(m_pData - n));
			}
			Iterator& operator-=(const difference_type& n)
			{
				m_pData -= n;
				return *this;
			}
			reference operator*() const
			{
				return *m_pData;
			}
			pointer operator->() const
			{
				return m_pData;
			}
			reference operator[](const difference_type& n) const
			{
				return m_pData[n];
			}
			bool operator == (const Iterator& it) const
			{
				return m_pData == it.m_pData;
			}
			bool operator != (const Iterator& it) const
			{
				return !(*this == it);
			}
			difference_type operator - (const Iterator& it) const
			{
				return m_pData - it.m_pData;
			}
			bool operator < (const Iterator& it) const
			{
				return m_pData < it.m_pData;
			}
			bool operator > (const Iterator& it) const
			{
				return m_pData > it.m_pData;
			}
			bool operator <= (const Iterator& it)
			{
				return !(*this > it);
			}
			bool operator >= (const Iterator& it)
			{
				return !(*this < it);
			}
		};


		template <class T> using iterator				= Iterator<T>;
		template <class T> using const_iterator			= Iterator < const T >;
		template <class T> using reverse_iterator		= std::reverse_iterator < Iterator<T> >;
		template <class T> using const_reverse_iterator = std::reverse_iterator < Iterator< const T> >;
	};
};

// global operators for array Iterator
template<typename T>
typename mfc::array::Iterator<T> operator+(
	const mfc::array::Iterator<T>& it,
	typename const mfc::array::Iterator<T>::difference_type& n)
{
	return mfc::array::Iterator<T>(it + n);
}
template<typename T>
typename mfc::array::Iterator<T> operator+(
	typename const mfc::array::Iterator<T>::difference_type& n,
	const mfc::array::Iterator<T>& it)
{
	return mfc::array::Iterator<T>(it + n);
}
template<typename T>
typename mfc::array::Iterator<T> operator-(
	const mfc::array::Iterator<T>& it,
	typename const mfc::array::Iterator<T>::difference_type& n)
{
	return mfc::array::Iterator<T>(it - n);
}
template<typename T>
typename mfc::array::Iterator<T> operator-(
	typename const mfc::array::Iterator<T>::difference_type& n,
	const mfc::array::Iterator<T>& it)
{
	return mfc::array::Iterator<T>(it - n);
}



// support for range-based for.(C++11)
template <class T>
auto begin(const T& arr) -> 
	typename std::enable_if<
		mfc::traits::is_array<T>::value,
		typename mfc::array::const_iterator<T>
	>::type
{
	return typename mfc::array::const_iterator<T>(arr.GetData());
}
template <class T>
auto end(const T& arr) ->
	typename std::enable_if<
		mfc::traits::is_array<T>::value,
		typename mfc::array::const_iterator<T>
	>::type
{
	return typename mfc::array::const_iterator<T>(arr.GetData() + arr.GetSize());
}
template <class T>
auto begin(T& arr) ->
	typename std::enable_if<
		mfc::traits::is_array<T>::value,
		typename mfc::array::iterator<T>
	>::type
{
	return typename mfc::array::iterator<T>(arr.GetData());
}
template <class T>
auto end(T& arr) -> 
	typename std::enable_if<
		mfc::traits::is_array<T>::value,
		typename mfc::array::iterator<T>
	>::type
{
	return typename mfc::array::iterator<T>(arr.GetData() + arr.GetSize());
}

template <class T>
auto rbegin(const T& arr) ->
	typename std::enable_if<
		mfc::traits::is_array<T>::value,
		typename mfc::array::const_reverse_iterator<T>
	>::type
{
	return typename mfc::array::const_reverse_iterator<T>(end(arr));
}
template <class T>
auto rend(const T& arr) ->
	typename std::enable_if<
		mfc::traits::is_array<T>::value,
		typename mfc::array::const_reverse_iterator<T>
	>::type
{
	return typename mfc::array::const_reverse_iterator<T>(begin(arr));
}
template <class T>
auto rbegin(T& arr) ->
	typename std::enable_if<
		mfc::traits::is_array<T>::value,
		typename mfc::array::reverse_iterator<T>
	>::type
{
	return typename mfc::array::reverse_iterator<T>(end(arr));
}
template <class T>
auto rend(T& arr) ->
	typename std::enable_if<
		mfc::traits::is_array<T>::value,
		typename mfc::array::reverse_iterator<T>
	>::type
{
	return typename mfc::array::reverse_iterator<T>(begin(arr));
}



// CArray with C++ 0x.
template <class TYPE, class ARG_TYPE = const TYPE&>
class CArray0x : public CArray<TYPE, ARG_TYPE>
{
public:
	using base						=  CArray<TYPE, ARG_TYPE>;

	using iterator					= typename mfc::array::iterator<base>;
	using const_iterator			= typename mfc::array::const_iterator<base>;
	using reverse_iterator			= typename mfc::array::reverse_iterator<base>;
	using const_reverse_iterator	= typename mfc::array::const_reverse_iterator<base>;

public:
	CArray0x() = default;
	~CArray0x() = default;

	CArray0x(const base& arr) = delete;
	CArray0x(const CArray0x<TYPE, ARG_TYPE>& arr) = delete;

	CArray0x(base&& arr)
	{
		*this = std::forward<base>(arr);
	}
	CArray0x(CArray0x<TYPE, ARG_TYPE>&& arr)
	{
		*this = std::forward<CArray0x<TYPE, ARG_TYPE>>(arr);
	}

	// initializer list
	CArray0x(std::initializer_list<TYPE> list)
	{
		int size = list.size();
		SetSize(size);
		int i = 0;
		for (auto e : list)
		{
			SetAt(i, e);
			++i;
		}
	}

	CArray0x& operator = (base&& arr)
	{
		//TYPE* m_pData;   // the actual array of data
		//INT_PTR m_nSize;     // # of elements (upperBound - 1)
		//INT_PTR m_nMaxSize;  // max allocated
		//INT_PTR m_nGrowBy;   // grow amount

		// We can't access the protected members of the argument(arr). 
		// So to get the address of the protected members, offset to the member from the address of the head.
		static size_t offset_pData		= mfc::utility::offset_of(&CArray0x::m_pData);
		static size_t offset_nSize		= mfc::utility::offset_of(&CArray0x::m_nSize);
		static size_t offset_nMaxSize	= mfc::utility::offset_of(&CArray0x::m_nMaxSize);
		static size_t offset_nGrowBy	= mfc::utility::offset_of(&CArray0x::m_nGrowBy);

		BYTE* head			= (BYTE*)&arr;								// head position of arr
		TYPE** pData		= (TYPE**)(head + offset_pData);			// offset to m_pData from head
		INT_PTR* pSize		= (INT_PTR*)(head + offset_nSize);			// offset to m_nSize from head
		INT_PTR* pMaxSize	= (INT_PTR*)(head + offset_nMaxSize);		// offset to m_nMaxSize from head
		INT_PTR* pGrowBy	= (INT_PTR*)(head + offset_nGrowBy);		// offset to m_nGrowBy from head

		// move members to this
		m_pData		= *pData;
		m_nSize		= *pSize;
		m_nMaxSize	= *pMaxSize;
		m_nGrowBy	= *pGrowBy;

		// unuse moved object(reference CArray constructor)
		*pData = nullptr;
		*pSize = *pMaxSize = *pGrowBy = 0;

		return *this;
	}
	CArray0x& operator = (CArray0x<TYPE, ARG_TYPE>&& arr)
	{
		return *this = std::forward<base>(arr);
	}


	// iterator support
	iterator				begin()			{ return ::begin((base&)(*this)); }
	const_iterator			begin() const	{ return ::begin(*this); }

	iterator				end()			{ return ::end((base&)*this); }
	const_iterator			end() const		{ return ::end(*this); }

	reverse_iterator		rbegin()		{ return reverse_iterator(end()); }
	const_reverse_iterator	rbegin() const	{ return const_reverse_iterator(end()); }

	reverse_iterator		rend()			{ return reverse_iterator(begin()); }
	const_reverse_iterator	rend() const	{ return const_reverse_iterator(begin()); }
};
