#include "stdafx.h"
#include "CppUnitTest.h"
#include <mmaccel/keyboard.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace mmaccel
{
	TEST_CLASS( KeyboardTest )
	{
	public:
		TEST_METHOD( KeysCombinationEqual )
		{
			mmaccel::keys_combination keys{ VK_CONTROL, 'A' };
			mmaccel::keys_combination keys2{ VK_CONTROL, 'B' };

			Assert::IsTrue( keys == keys );
			Assert::IsTrue( keys != keys2 );
		}

		TEST_METHOD( KeyToString )
		{
			{
				mmaccel::keys_combination keys{ 'A', VK_CONTROL };
				Assert::IsTrue( mmaccel::keys_to_string( keys ) == std::string( u8"ctrl + a" ) );
			}
			{
				mmaccel::keys_combination keys{ 'A' };
				Assert::IsTrue( mmaccel::keys_to_string( keys ) == std::string( u8"a" ) );
			}
		}

		TEST_METHOD( StringToKeys )
		{
			auto const keys = mmaccel::string_to_keys( u8"ctrl + a" );
			Assert::IsTrue( keys[0] == VK_CONTROL );
			Assert::IsTrue( keys[1] == 'A' );
		}
	};

} // namespace mmaccel