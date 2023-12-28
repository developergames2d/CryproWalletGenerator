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
#pragma warning(push)
#pragma warning(disable:4005)
#include <MyLib\BigInteger.hpp>
#pragma warning(pop)

using namespace std;

namespace crypto
{
	extern const MyString passphrase::symbols = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	MyString passphrase::GetStringFromBytes(std::vector<unsigned __int8> bytes)
	{
		if(passphrase::symbols.getLength() == 0)
			throw MyException() << __FILE__ << ":" << __LINE__;

		BigInteger number = 0;
		for (size_t i = 0; i < bytes.size(); ++i)
			number = number * 0x100 + (int)bytes[bytes.size() - 1 - i];
		BigInteger max_n = BigInteger(0x100).qpow(bytes.size()) - 1;
		MyString result;
		while (max_n > 0)
		{
			BigInteger rest_b = (number % (BigInteger)passphrase::symbols.getLength());
			size_t rest = 0;
			for(size_t j = 0; j < rest_b.length(); ++j)
				rest = rest * 10 + rest_b.getDigitFromLast(rest_b.length() - 1 - j);
			result = MyString(passphrase::symbols[rest % passphrase::symbols.getLength()]) + result;
			number /= passphrase::symbols.getLength();
			max_n /= passphrase::symbols.getLength();
		}

		return result;
	}
}