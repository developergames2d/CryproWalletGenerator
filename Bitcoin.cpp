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

#include "Crypto.hpp"
#include "SHA256.hpp"

using namespace std;

namespace crypto
{
	void bitcoin::AddSHA(std::vector<unsigned __int8>& bytes)
	{
		SHA256 sha;
		sha.update(bytes.data(), bytes.size());

		bytes.push_back(sha.digest()[0]);
	}

	std::vector<MyString> bitcoin::GetBIP39Mnemonic24(std::vector<unsigned __int8> bytes)
	{
		const size_t WORD_BITS = 11;
		const size_t WORDS_COUNT = 24;

		if (bytes.size() != WORD_BITS * WORDS_COUNT / 8)
			throw MyException() << __FILE__ << ":" << __LINE__;

		SHA256 sha;
		sha.update(bytes.data(), WORD_BITS * WORDS_COUNT / 8 - 1);

		if (sha.digest()[0] != bytes.back())
			throw MyException() << __FILE__ << ":" << __LINE__;

		auto bits = GetBitsFromBytes(bytes);
		if (bits.getLength() != WORD_BITS * WORDS_COUNT)
			throw MyException() << __FILE__ << ":" << __LINE__;

		vector<int> numbers;
		for (size_t i = 0; i < WORDS_COUNT; ++i)
		{
			int current_number = 0;
			for (size_t j = 0; j < WORD_BITS; ++j)
				current_number = current_number * 2 + (bits[i * WORD_BITS + j] - '0');
			if (current_number >= BIP39_SIZE)
				throw MyException() << __FILE__ << ":" << __LINE__;
			numbers.push_back(current_number);
		}

		vector<MyString> mnemonic;
		for (size_t i = 0; i < numbers.size(); ++i)
			mnemonic.push_back(BIP39_WORDS[numbers[i]]);

		return mnemonic;
	}
}