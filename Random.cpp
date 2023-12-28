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
#include <SFML\Graphics.hpp>
#include <sys/stat.h>
#include "Crypto.hpp"

using namespace std;

off_t GetFileLength(std::string const& filename)
{
	struct stat st;
	if (stat(filename.c_str(), &st) == -1)
		return 0;
	return st.st_size;
}

vector<unsigned __int8> GenerateRandomBytes(size_t count_wallets, MyString output)
{
	char randomstring[1024] = "";
	cout << "Print some string and press Enter." << endl;
	while (randomstring[0] == 0)
		gets_s(randomstring);


	vector<unsigned __int8> randombytes_file;
	const size_t randombytes_file_max = 128 * 1024;

	while (randombytes_file.empty())
	{
		cout << "Print filename with entropy or * for skipping." << endl;
		char filename[300];

		gets_s(filename);

		if (!strcmp(filename, "*"))
		{
			randombytes_file.push_back(time(nullptr) % 0x100);
			continue;
		}
		FILE * rnd;
		fopen_s(&rnd, filename, "rb");
		if (!rnd)
		{
			cout << "Error with open." << endl;
			continue;
		}

		size_t filesize = GetFileLength(filename);
		for (size_t i = 0; i < filesize && i < randombytes_file_max; ++i)
			randombytes_file.push_back(fgetc(rnd));

		fclose(rnd);
		if (randombytes_file.empty())
			cout << "Error: file is empty." << endl;
	}


	const size_t SIZE_WALLET = crypto::PRIVATE_KEY_BYTES;
	const size_t MAX_SIZE = count_wallets * SIZE_WALLET;
	const size_t BYTES_RESET = 8 * 1024 + time(NULL) % 1234;
	const __int64 TIME_RESET = 7'000'000 + time(NULL) % 1000 * 3000;
	bool reseted_bytes = false;
	bool reseted_time = false;
	const __int64 RAND_N = 7 + (rand() + time(NULL)) % 11;

	vector<unsigned __int8> result;


	sf::RenderWindow rw(sf::VideoMode(200, 200), "!");

	cout << "MOVE YOUR MOUSE!" << endl;

	sf::Clock clk;
	clk.restart();

	SHA256 sha;
	sha.update(randomstring);
	sha.update(randombytes_file.data(), randombytes_file.size());
	randombytes_file.clear();


	FILE * output_f;
	fopen_s(&output_f, output.operator const char *(), "w");

	auto mp = sf::Mouse::getPosition(rw);

	auto UPDATE_SHA = [&](int k)->void
	{
		char new_bytes[10000];
		sprintf_s(new_bytes, "%lld%s%d%d%d%lld%d", clk.getElapsedTime().asMicroseconds(), sha.toString(sha.digest()).data(), mp.x, mp.y, k, (__int64)result.size(), (int)time(NULL));
		sha.update((unsigned __int8 *)new_bytes, strlen(new_bytes));

		if (output_f && reseted_bytes && reseted_time)
			fprintf_s(output_f, "%s\n", new_bytes);
	};



	while (!reseted_bytes || !reseted_time || result.size() < MAX_SIZE)
	{
		if (!reseted_time && clk.getElapsedTime().asMicroseconds() >= TIME_RESET)
		{
			result.clear();
			reseted_time = true;
		}

		sf::Event event;

		while (rw.pollEvent(event))
			;

		auto mp1 = sf::Mouse::getPosition(rw);
		if (mp == mp1)
			continue;
		mp = mp1;

		if (reseted_bytes && reseted_time)
		{
			const __int64 n = sha.digest()[0] * 0x1000 + sha.digest()[1] * 0x10 + +sha.digest()[2] * 0x10 + +sha.digest()[3];
			if (n % RAND_N != 0)
			{
				UPDATE_SHA(0);
				continue;
			}
		}

		for (int k = 0; k < 1; ++k)
		{
			UPDATE_SHA(k);

			for (size_t i = 0; (result.size() < MAX_SIZE || !reseted_bytes || !reseted_time) && i < sha.digest().size(); ++i)
				result.push_back(sha.digest()[i]);
			if (!reseted_bytes && result.size() >= BYTES_RESET)
			{
				result.clear();
				reseted_bytes = true;
			}
		}

		if (!reseted_bytes || !reseted_time)
			printf("Create entropy. %6.2lf%% %6.2lf%%\n", (reseted_bytes ? 1 : (double)result.size() / BYTES_RESET) * 100, (reseted_time ? 1 : (double)clk.getElapsedTime().asMicroseconds() / TIME_RESET) * 100);
		else
			printf_s("Generate wallets. %20llu/%llu (%6.2lf%%)\n", result.size() / SIZE_WALLET, MAX_SIZE / SIZE_WALLET, (double)result.size() / MAX_SIZE * 100);
	}


	if (!reseted_time || !reseted_bytes)
		cout << "Error reset" << endl;

	if (output_f)
		fclose(output_f);

	bool check_test = false;
	if (check_test)
	{
		__int64 counts[0x100];
		for (int i = 0; i < 0x100; ++i)
			counts[i] = 0;

		for (size_t i = 0; i < result.size(); ++i)
			++counts[result[i]];

		__int64 c_min = MAX_SIZE + 1;
		__int64 c_max = -1;

		for (int i = 0; i < 0x100; ++i)
		{
			if (counts[i] < c_min)
				c_min = counts[i];
			if (counts[i] > c_max)
				c_max = counts[i];
		}
		printf_s("%20.10lf %20.10lf\n%20.10lf %20.10lf\n\n\n\n", (double)c_min / MAX_SIZE, (double)MAX_SIZE / c_min, (double)c_max / MAX_SIZE, (double)MAX_SIZE / c_max);
	}

	return result;
}