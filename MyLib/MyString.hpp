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
#ifdef _DEBUG
#pragma comment(lib, "MyLib/MyString.lib")
#else
#pragma comment(lib, "MyLib/MyString_Release.lib")
#endif
#include <iostream>
#include <sstream>
#include <varargs.h>

class BigInteger;

class MyString
{
private:
	char *data;
	size_t size;
public:
	MyString();
	MyString(char c);
	MyString(const char *s);
	MyString(const MyString& other);
	~MyString();

	static MyString GetStringFromNumber(__int64 num, __int64 min_width = -1, char front = '0');
	static MyString GetStringFromNumber(BigInteger num, __int64 min_width = -1, char front = '0');

	//������������� ������� � ����� ������.
	MyString& operator += (const char c);

	//�������������� � const char*
	operator const char *() const;
	operator std::string() const;

	//���������� ������ �� �������� ������ � ���������� ������. 
	void scan(std::istream& is);

	//���������� ������ �� ����� �� ������� ����������� ������� ��� ����� ����� � ���������� ������. 
	void fscan(FILE *fin);
	//���������� ������ �� ����� �� ������� ��� �������� ������ ��� ����� ����� � ���������� ������.
	//���������� feof
	bool fgetline(FILE *fin);

	//��������� � ������ �������
	bool operator==(const char* other)const;
	bool operator!=(const char* other)const;
	MyString operator=(const char* other);
	MyString operator=(const std::string other);
	MyString operator=(const MyString& other);

	size_t getLength()const;
	//������������� ������ ������ ��������
	void doForEach(void(*f)(char&));
	//������������� ������ ������ ��������
	void doForEach(char(*f)(char));
	//��� ������� ������� ������ ������
	template<typename T> void doForEach_const(T(*nextT)(T prev, char symbol), T&t) const
	{
		for (size_t i = 0; i < size; ++i)
			t = nextT(t, data[i]);
	}
	operator bool() { return data != nullptr; }

	MyString& operator += (const char *str);
	MyString& operator += (const MyString& other);
	MyString operator + (const MyString& other);

	char operator[](size_t ind) const;
	//! ��� ������� ���������� � ���������. "12345678".getSubStr(2, 4) == "345"
	MyString getSubStr(size_t ind_start, size_t ind_last) const;
};

std::ostream& operator<<(std::ostream& os, const MyString& str);
std::istream& operator>>(std::istream& is, MyString& str);
std::string& operator>>(std::string& is, MyString& str);