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

#pragma once

#include <MyLib\MyString.hpp>

class MyException
{
private:
	MyString message;
public:
	MyException()
	{
	}
	MyException(const char *mes)
		:message(mes)
	{
	}
	MyException(const MyException& other)
		:message(other.message)
	{
	}
	~MyException()
	{
	}
	friend std::ostream& operator<<(std::ostream& os, const MyException& exc)
	{
		os << exc.message;
		return os;
	}

	MyException& operator<<(const char * s)
	{
		message += s;
		return *this;
	}
	MyException& operator<<(MyString s)
	{
		message += s;
		return *this;
	}
	MyException& operator<<(char c)
	{
		message += c;
		return *this;
	}
	//for __LINE__
	MyException& operator<<(int n)
	{
		if (n == 0)
			message += '0';
		if (n < 0)
			message += '-';
		MyString number;
		while (n)
		{
			number = MyString(n % 10 + '0') + number;
			n /= 10;
		}
		message += number;
		return *this;
	}
};