#pragma once

#include "../winapi/menu.hpp"
#include "../winapi/directory.hpp"
#include "message_handler.hpp"
#include "../utility/type_tuple.hpp"

namespace mmaccel
{
	template <DWORD ControlID>
	struct menu_command
	{
		using function_type = void();
		static constexpr auto id = ControlID;
	};

	template <DWORD ID, DWORD... SubItems>
	class menu
	{
		winapi::loaded_menu_handle root_;
		message_handler< menu_command< SubItems >... > mh_;

	public:
		menu() = default;

		menu( HWND hwnd, boost::wstring_ref path, boost::wstring_ref root_name ) :
			root_( winapi::load_menu( path, ID ) )
		{
			auto const src = winapi::get_menu( hwnd );
			winapi::insert_menu( src, winapi::get_menu_item_count( src ), winapi::get_sub_menu( root_, 0 ), root_name.data() );

			DrawMenuBar( hwnd );
		}

		template <typename Message, typename F>
		void assign_handler(Message, F&& f)
		{
			mh_.assign( Message(), std::forward< F >( f ) );
		}

		void on_command( WPARAM wparam )
		{
			if( !root_ ) {
				return;
			}

			if( HIWORD( wparam ) != 0 ) {
				return;
			}

			invoke( mh_, LOWORD( wparam ) );
		}

	private:
		template <typename... Messages>
		static void invoke( message_handler< Messages... > const& mh, DWORD id )
		{
			invoke_impl( type_tuple< Messages... >(), mh, id );
		}

		template <typename Message, typename... Rest, typename... MH>
		static void invoke_impl( type_tuple< Message, Rest... >, message_handler<MH...> const& mh, DWORD id )
		{
			if( id == Message::id ) {
				mh.invoke( Message() );
				return;
			}

			invoke_impl( type_tuple< Rest... >(), mh, id );
		}

		template <typename... MH>
		static void invoke_impl( type_tuple<>, message_handler< MH... > const&, DWORD )
		{ }
	};

} // namespace mmaccel
