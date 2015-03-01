#pragma once

namespace mfc
{
	namespace utility
	{
		template<class T, class C>
		std::size_t offset_of(T(C::*pm))
		{
			return reinterpret_cast<std::size_t>(
				&reinterpret_cast<const volatile char&>(((C*)0)->*pm)
				);
		}
	};
};