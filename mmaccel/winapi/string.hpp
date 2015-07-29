#pragma once

#include "../platform.hpp"
#include <vector>
#include <string>
#include <boost/utility/string_ref.hpp>

namespace winapi
{
	inline std::wstring multibyte_to_widechar(boost::string_ref src, int code)
	{
		auto const sz = MultiByteToWideChar( code, 0, src.data(), static_cast< int >( src.size() ), nullptr, 0 );
		if( !sz ) {
			return{};
		}

		std::wstring dst;
		dst.resize( sz );
		auto const result = MultiByteToWideChar( code, 0, src.data(), static_cast< int >( src.size() ), &dst[0], static_cast< int >( dst.size() ) );
		if( !result ) {
			return{};
		}

		return dst;
	}

} // namespace winapi