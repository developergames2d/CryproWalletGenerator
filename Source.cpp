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

#include <iostream>
#include <chrono>
#include <ctime>
#include "SHA256.hpp"
#include "Crypto.hpp"
#include "Random.hpp"
#include "CRC32.hpp"
#include <MyLib\MyException.hpp>
#include "Other.hpp"

using namespace std;

enum class Coin { Bitcoin, Monero, Dogecoin, Litecoin, Solana, Incorrect };

int main()
{
	bool GENERATE_FIRST = false;
	try
	{
		Coin coin = Coin::Incorrect;

		while (coin == Coin::Incorrect)
		{
			cout << "For what coin generate wallets? (Bitcoin, Monero, Dogecoin, Litecoin, Solana)" << endl;

			MyString s_coin;
			cin >> s_coin;

			s_coin.doForEach([](char c)->char { return (char)toupper(c); });

			if (s_coin == "BITCOIN" || s_coin == "BTC")
				coin = Coin::Bitcoin;
			if (s_coin == "MONERO" || s_coin == "XMR")
				coin = Coin::Monero;
			if (s_coin == "DOGECOIN" || s_coin == "DOGE")
				coin = Coin::Dogecoin;
			if (s_coin == "LITECOIN" || s_coin == "LTC")
				coin = Coin::Litecoin;
			if (s_coin == "SOLANA" || s_coin == "SOL")
				coin = Coin::Solana;

			if (static_cast<int>(coin) >= static_cast<int>(Coin::Incorrect) || static_cast<int>(coin) < 0)
				cout << "Error input" << endl;
		}


		cout << "How many wallets generate?" << endl;
		size_t wallets_count = 0;
		cin >> wallets_count;

		if (!wallets_count)
			return 0;
		
		vector<unsigned __int8> all_bytes;
		if (GENERATE_FIRST)
			all_bytes = GenerateFirstBytes(wallets_count);
		else
			all_bytes = GenerateRandomBytes(wallets_count);
		
		


		FILE * out_bin = nullptr;
		FILE * out_hex = nullptr;
		FILE * out_mnm = nullptr;
		FILE * out_dog = nullptr;
		FILE * out_ltc = nullptr;

		if (coin == Coin::Bitcoin || coin == Coin::Solana)
		{
			fopen_s(&out_bin, "out_bin.txt", "w");
			fopen_s(&out_mnm, "out_mnm.txt", "w");
			if (!out_bin || !out_mnm)
				throw MyException() << __FILE__ << ":" << __LINE__;
		}

		if (coin == Coin::Dogecoin)
		{
			fopen_s(&out_dog, "out_dog.txt", "w");
			if (!out_dog)
				throw MyException() << __FILE__ << ":" << __LINE__;
		}

		if (coin == Coin::Litecoin)
		{
			fopen_s(&out_ltc, "out_ltc.txt", "w");
			if (!out_ltc)
				throw MyException() << __FILE__ << ":" << __LINE__;
		}

		fopen_s(&out_hex, "out_hex.txt", "w");
		if (!out_hex)
			throw MyException() << __FILE__ << ":" << __LINE__;


		const size_t SIZE_WALLET = crypto::PRIVATE_KEY_BYTES;

		if (all_bytes.size() % SIZE_WALLET != 0)
			throw MyException() << __FILE__ << ":" << __LINE__;

		for (size_t k = 0; k < all_bytes.size() / SIZE_WALLET; ++k)
		{
			vector<unsigned __int8> bytes;
			for (size_t i = 0; i < SIZE_WALLET; ++i)
				bytes.push_back(all_bytes[k * SIZE_WALLET + i]);

			if (coin == Coin::Bitcoin || coin == Coin::Solana)
			{
				crypto::bitcoin::AddSHA(bytes);

				MyString bin = crypto::GetBitsFromBytes(bytes);
				MyString hex = crypto::GetHexFromBytes(bytes);
				auto mnemonic = crypto::bitcoin::GetBIP39Mnemonic24(bytes);

				fprintf_s(out_bin, "%s %s\n", MyString::GetStringFromNumber(k + 1, 10, ' ').operator const char *(), bin.operator const char *());
				fprintf_s(out_hex, "%s %s\n", MyString::GetStringFromNumber(k + 1, 10, ' ').operator const char *(), hex.operator const char *());

				fprintf_s(out_mnm, "%s ", MyString::GetStringFromNumber(k + 1, 10, ' ').operator const char *());
				for (size_t i = 0; i < mnemonic.size(); ++i)
					fprintf_s(out_mnm, "%12s", mnemonic[i].operator const char *());
				fprintf_s(out_mnm, "\n");
			}
			if (coin == Coin::Monero)
			{
				MyString hex = crypto::GetHexFromBytes(bytes);
				fprintf_s(out_hex, "%s        %s\n", MyString::GetStringFromNumber(k + 1, 10, ' ').operator const char *(), hex.operator const char *());
			}
			if (coin == Coin::Dogecoin || coin == Coin::Litecoin)
			{
				MyString hex = crypto::GetHexFromBytes(bytes);
				MyString dogltc = crypto::passphrase::GetStringFromBytes(bytes);
				fprintf_s(out_hex, "%s        %s\n", MyString::GetStringFromNumber(k + 1, 10, ' ').operator const char *(), hex.operator const char *());
				fprintf_s(coin == Coin::Dogecoin ? out_dog : out_ltc, "%s        %s\n", MyString::GetStringFromNumber(k + 1, 10, ' ').operator const char *(), dogltc.operator const char *());
			}
		}

		if (out_bin)
			fclose(out_bin);
		if (out_hex)
			fclose(out_hex);
		if (out_mnm)
			fclose(out_mnm);
		if (out_dog)
			fclose(out_dog);
		if (out_ltc)
			fclose(out_ltc);


		MyString sss = MyString("!!!ERROR ON LINE ") + MyString::GetStringFromNumber(__LINE__) + MyString("!!!");
		if (coin == Coin::Bitcoin || coin == Coin::Solana)
			sss = "out_bin.txt, out_hex.txt and out_mnm.txt";
		if (coin == Coin::Monero)
			sss = "out_hex.txt";
		if (coin == Coin::Dogecoin)
			sss = "out_hex.txt and out_dog.txt";
		if (coin == Coin::Litecoin)
			sss = "out_hex.txt and out_ltc.txt";
		cout << "Your wallets was created. See file(s) " << sss << ".\n" << "Save it in a safe place and ERASE these files beyond recovery (do not just delete or shift+delete!)." << endl << endl;

	}
	catch (const MyException & e)
	{
		cout << e << endl;
	}
	catch (...)
	{
		cout << "Fatal error: unknown exception." << endl;
	}
	system("pause");
	return 0;
}