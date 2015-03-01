#pragma once

#include <type_traits>
#include <afxtempl.h>

namespace mfc
{
	namespace traits
	{
#define MFC_DEFINE_HAS_METHOD(name, method)	\
	template <typename T>	\
	struct name	\
			{	\
	private:	\
		template < typename U >	\
		static auto check(const U& x) -> decltype(x.##method##(), std::true_type());	\
		static auto check(...) -> decltype(std::false_type());	\
	public:	\
		typedef decltype(check<T>(std::declval<T>())) type;	\
		static bool const value = type::value;	\
			};


		// for CArray, CByteArray, CWordArray, CDWordArray, CUIntArray, CPtrArray, CObArray, CStringArray
		MFC_DEFINE_HAS_METHOD(is_array, GetData)

		template <typename T>
		struct array_type
		{
			typedef typename std::remove_pointer<decltype(std::declval<T>().GetData())>::type type;
		};


		// for CList, CPtrList, CObList, CStringList, CTypedPtrList
		MFC_DEFINE_HAS_METHOD(is_list, GetHeadPosition)


		MFC_DEFINE_HAS_METHOD(is_map, GetHashTableSize)

	};
};