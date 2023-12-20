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
	#pragma comment(lib, "MyLib/BigInteger.lib")
#else
	#pragma comment(lib, "MyLib/BigInteger_Release.lib")
#endif


#include < cstdio >
#include < new >
#include < cstddef >
#include < cstring >
#include < cstdarg >
#include < ctime >
#include < conio.h >
#include < cctype >
#include < iostream >
#include < vector >
#include "../../MyString/MyString/MyString.hpp"

#define ABS(x) ((x) > 0 ? (x) : (-(x)))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define SGN(x) ((x) > 0 ? 1 : (-1))
#define SQR(x) ((x)*(x))

class BigInteger
{

private:
	std::vector<__int8>data;
	char sign;

	bool isMoreABS(const BigInteger& other) const;
	void createFromVector_reverse(const std::vector<__int8>& _data, size_t length, size_t start);
	void mulpow10(size_t pow);
public:
	BigInteger();
	BigInteger(int _Value);
	BigInteger(unsigned int _Value);
	BigInteger(__int64 _Value);
	BigInteger(unsigned __int64 _Value);
	BigInteger(const char *_Value);
	BigInteger(const BigInteger& other);
	BigInteger operator=(const BigInteger& other);
	BigInteger operator+()const;
	BigInteger operator+=(const BigInteger& other);
	BigInteger operator+(const BigInteger& other) const;
	BigInteger operator+(const __int8 other) const;
	BigInteger operator+(const unsigned __int8 other) const;
	BigInteger operator+(const __int16 other) const;
	BigInteger operator+(const unsigned __int16 other) const;
	BigInteger operator+(const __int32 other) const;
	BigInteger operator+(const unsigned __int32 other) const;
	BigInteger operator+(const __int64 other) const;
	BigInteger operator+(const unsigned __int64 other) const;
	BigInteger operator+(const char *other) const;
	BigInteger operator-=(const BigInteger& other);
	BigInteger operator-(const BigInteger& other) const;
	BigInteger operator-(const __int8 other) const;
	BigInteger operator-(const unsigned __int8 other) const;
	BigInteger operator-(const __int16 other) const;
	BigInteger operator-(const unsigned __int16 other) const;
	BigInteger operator-(const __int32 other) const;
	BigInteger operator-(const unsigned __int32 other) const;
	BigInteger operator-(const __int64 other) const;
	BigInteger operator-(const unsigned __int64 other) const;
	BigInteger operator-(const char *other) const;
	BigInteger operator-()const;
	/*friend BigInteger operator-(const __int8 other, const BigInteger num);
	friend BigInteger operator-(const unsigned __int8 other, const BigInteger num);
	friend BigInteger operator-(const __int16 other, const BigInteger num);
	friend BigInteger operator-(const unsigned __int16 other, const BigInteger num);
	friend BigInteger operator-(const __int32 other, const BigInteger num);
	friend BigInteger operator-(const unsigned __int32 other, const BigInteger num);
	friend BigInteger operator-(const __int64 other, const BigInteger num);
	friend BigInteger operator-(const unsigned __int64 other, const BigInteger num);
	friend BigInteger operator-(const char *other, const BigInteger num);*/
	BigInteger operator*=(const BigInteger& other);
	BigInteger operator*(const BigInteger& other) const;
	BigInteger operator*(const __int8 other) const;
	BigInteger operator*(const unsigned __int8 other) const;
	BigInteger operator*(const __int16 other) const;
	BigInteger operator*(const unsigned __int16 other) const;
	BigInteger operator*(const __int32 other) const;
	BigInteger operator*(const unsigned __int32 other) const;
	BigInteger operator*(const __int64 other) const;
	BigInteger operator*(const unsigned __int64 other) const;
	BigInteger operator*(const char *other) const;
	BigInteger operator/=(const BigInteger& other);
	BigInteger operator/(const BigInteger& other) const;
	BigInteger operator/(const __int8 other) const;
	BigInteger operator/(const unsigned __int8 other) const;
	BigInteger operator/(const __int16 other) const;
	BigInteger operator/(const unsigned __int16 other) const;
	BigInteger operator/(const __int32 other) const;
	BigInteger operator/(const unsigned __int32 other) const;
	BigInteger operator/(const __int64 other) const;
	BigInteger operator/(const unsigned __int64 other) const;
	BigInteger operator/(const char *other) const;
	BigInteger operator%=(const BigInteger& other);
	BigInteger operator%(const BigInteger& other) const;
	BigInteger operator%(const __int8 other) const;
	BigInteger operator%(const unsigned __int8 other) const;
	BigInteger operator%(const __int16 other) const;
	BigInteger operator%(const unsigned __int16 other) const;
	BigInteger operator%(const __int32 other) const;
	BigInteger operator%(const unsigned __int32 other) const;
	BigInteger operator%(const __int64 other) const;
	BigInteger operator%(const unsigned __int64 other) const;
	BigInteger operator%(const char *other) const;
	BigInteger operator++();
	BigInteger operator++(int);
	BigInteger operator--();
	BigInteger operator--(int);
	bool operator==(const BigInteger& other)const;
	bool operator==(const __int8 other)const;
	bool operator==(const unsigned __int8 other)const;
	bool operator==(const __int16 other)const;
	bool operator==(const unsigned __int16 other)const;
	bool operator==(const __int32 other)const;
	bool operator==(const unsigned __int32 other)const;
	bool operator==(const __int64 other)const;
	bool operator==(const unsigned __int64 other)const;
	bool operator==(const char *other)const;
	bool operator!=(const BigInteger& other)const;
	bool operator!=(const __int8 other)const;
	bool operator!=(const unsigned __int8 other)const;
	bool operator!=(const __int16 other)const;
	bool operator!=(const unsigned __int16 other)const;
	bool operator!=(const __int32 other)const;
	bool operator!=(const unsigned __int32 other)const;
	bool operator!=(const __int64 other)const;
	bool operator!=(const unsigned __int64 other)const;
	bool operator!=(const char *other)const;
	bool operator>=(const BigInteger& other)const;
	bool operator>=(const __int8 other)const;
	bool operator>=(const unsigned __int8 other)const;
	bool operator>=(const __int16 other)const;
	bool operator>=(const unsigned __int16 other)const;
	bool operator>=(const __int32 other)const;
	bool operator>=(const unsigned __int32 other)const;
	bool operator>=(const __int64 other)const;
	bool operator>=(const unsigned __int64 other)const;
	bool operator>=(const char *other)const;
	bool operator>(const BigInteger& other)const;
	bool operator>(const __int8 other)const;
	bool operator>(const unsigned __int8 other)const;
	bool operator>(const __int16 other)const;
	bool operator>(const unsigned __int16 other)const;
	bool operator>(const __int32 other)const;
	bool operator>(const unsigned __int32 other)const;
	bool operator>(const __int64 other)const;
	bool operator>(const unsigned __int64 other)const;
	bool operator>(const char *other)const;
	bool operator<=(const BigInteger& other)const;
	bool operator<=(const __int8 other)const;
	bool operator<=(const unsigned __int8 other)const;
	bool operator<=(const __int16 other)const;
	bool operator<=(const unsigned __int16 other)const;
	bool operator<=(const __int32 other)const;
	bool operator<=(const unsigned __int32 other)const;
	bool operator<=(const __int64 other)const;
	bool operator<=(const unsigned __int64 other)const;
	bool operator<=(const char *other)const;
	bool operator<(const BigInteger& other)const;
	bool operator<(const __int8 other)const;
	bool operator<(const unsigned __int8 other)const;
	bool operator<(const __int16 other)const;
	bool operator<(const unsigned __int16 other)const;
	bool operator<(const __int32 other)const;
	bool operator<(const unsigned __int32 other)const;
	bool operator<(const __int64 other)const;
	bool operator<(const unsigned __int64 other)const;
	bool operator<(const char *other)const;
	operator bool()const;
	BigInteger div2();
	BigInteger gcd(const BigInteger& other)const;
	BigInteger pow(const BigInteger& other)const;
	BigInteger pow(const unsigned __int64 exponent)const;
	BigInteger pow(const unsigned __int32 exponent)const;
	BigInteger pow(const signed __int64 exponent)const;
	BigInteger pow(const signed __int32 exponent)const;
	BigInteger qpow(unsigned __int64 exponent)const;
	BigInteger qpmod(const BigInteger& exponent, const BigInteger& module)const;
	static BigInteger fact(size_t value);

	void print(std::ostream& os = std::cout)const;
	void println(std::ostream& os = std::cout)const;

	static BigInteger getRandom(bool reset = false);
	size_t length()const;
	signed __int64 lengthdiff()const;
	bool isSharedBy2()const;
	int getDigitFromLast(size_t position)const;
	void setDigitFromLast(int digit, int position);
	BigInteger lead(const BigInteger& module);
	BigInteger module()const;
	BigInteger div10();
	~BigInteger(){}
};
std::ostream& operator<<(std::ostream& os, const BigInteger& b);
std::istream& operator>>(std::istream& is, BigInteger& b);

BigInteger operator+(__int64 a, const BigInteger & b);
BigInteger operator+(unsigned __int64 a, const BigInteger & b);
BigInteger operator+(const char * a, const BigInteger & b);
BigInteger operator-(__int64 a, const BigInteger & b);
BigInteger operator-(unsigned __int64 a, const BigInteger & b);
BigInteger operator-(const char * a, const BigInteger & b);
BigInteger operator*(__int64 a, const BigInteger & b);
BigInteger operator*(unsigned __int64 a, const BigInteger & b);
BigInteger operator*(const char * a, const BigInteger & b);
BigInteger operator/(__int64 a, const BigInteger & b);
BigInteger operator/(unsigned __int64 a, const BigInteger & b);
BigInteger operator/(const char * a, const BigInteger & b);
BigInteger operator%(__int64 a, const BigInteger & b);
BigInteger operator%(unsigned __int64 a, const BigInteger & b);
BigInteger operator%(const char * a, const BigInteger & b);
