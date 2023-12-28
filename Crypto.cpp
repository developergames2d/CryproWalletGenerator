//!     Official link:
//!     https://github.com/developergames2d/CryproWalletGenerator/
//!     DONATE:
//!     	XMR:
//!     		87MnyP3mpxQBmCoQHM4H64RuaBZtP5zW2hGWu18YPujA94a18ypzpYT6jnNq68Q24yXwXAFDG2Vi91AgLNC76uEcR5WMoRp
//!     	BTC:
//!     		bc1qrg8agge2gcy75kct9g3cxeyl26ecjsx5wf4r8a
//!     	DOGE:
//!     		D9UD5v6xDAQZkBpJz1eP3Q1byGBC9dx5rd
//!     	Litecoin:
//!     		Latr7n7ATGEC9AGXbJW2D9SWQdQUu3am1C
//!         Solana:
//!             ET1Zbdun77T64e5EPBkyj13DZyLMmkjiB7nkVHak2q87

#include "Crypto.hpp"

using namespace std;

namespace crypto
{
	extern const size_t PRIVATE_KEY_BYTES = 32;

	MyString GetBitsFromBytes(std::vector<unsigned __int8> bytes)
	{
		MyString res;

		for (size_t i = 0; i < bytes.size(); ++i)
		{
			unsigned __int8 c = bytes[i];
			char str[9];
			for (int j = 0; j < 8; ++j)
			{
				str[7 - j] = c % 2 + '0';
				c >>= 1;
			}
			str[8] = '\0';
			res += str;
		}
		return res;
	}

	MyString GetHexFromBytes(std::vector<unsigned __int8> bytes)
	{
		MyString res;
		const char * HEX = "0123456789abcdef";

		for (size_t i = 0; i < bytes.size(); ++i)
		{
			unsigned __int8 c = bytes[i];
			res += HEX[c >> 4];
			res += HEX[c % 0x10];
		}
		return res;
	}
}