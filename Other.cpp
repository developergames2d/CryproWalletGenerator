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

#include "Other.hpp"
#include "Crypto.hpp"

using namespace std;

std::vector<unsigned __int8> GenerateFirstBytes(size_t count_wallets)
{
	const size_t SIZE_WALLET = crypto::PRIVATE_KEY_BYTES;
	const size_t MAX_SIZE = count_wallets * SIZE_WALLET;

	vector<unsigned __int8> result;

	for (unsigned __int64 current_wallet = 0; current_wallet < count_wallets; ++current_wallet)
	{
		vector<unsigned __int8> bytes(crypto::PRIVATE_KEY_BYTES, 0);

		unsigned __int64 temp = current_wallet;
		for (int i = 0; i < 8; ++i)
		{
			bytes[crypto::PRIVATE_KEY_BYTES - i - 1] = temp % 0x100;
			temp /= 0x100;
		}

		for (size_t i = 0; (result.size() < MAX_SIZE) && i < bytes.size(); ++i)
			result.push_back(bytes[i]);
	}

	return result;
}
