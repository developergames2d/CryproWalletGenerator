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

#include "MyString.hpp"
#include "../../BigInteger/BigInteger/BigInteger.hpp"

MyString::MyString()
{
	data = new char[1];
	data[0] = 0;
	size = 1;
}
MyString::MyString(char c)
{
	data = new char[2];
	data[0] = c;
	data[1] = 0;
	size = 2;
}
MyString::MyString(const char *s)
{
	data = new char[size = strlen(s) + 1];
	char *ptrThis = data;

	while (*ptrThis++ = *s++)
		;
	data[size - 1] = 0;
}
MyString::MyString(const MyString& other)
{
	data = new char[size = strlen(other.data) + 1];
	char *ptrThis = data;
	char *otherdata = other.data;
	while (*ptrThis++ = *otherdata++)
		;
	data[size - 1] = 0;
}
MyString::~MyString()
{
	delete[] data;
}
MyString& MyString::operator += (const char c)
{
	++size;
	if (data == 0)
	{
		data = new char[size = 1 + 1];
		data[0] = c;
		data[1] = 0;
		return *this;
	}
	char *newData = new char[size + 1];
	char *ptrThis = data, *ptrNew = newData, *ptrNewCurr = ptrNew;
	while (*ptrNewCurr++ = *ptrThis++)
		;
	ptrNewCurr[-1] = c;
	ptrNewCurr[0] = 0;
	delete[] data;
	data = ptrNew;

	return *this;
}
MyString::operator const char *()const
{
	return data;
}
MyString::operator std::string() const
{
	return std::string(data);
}
void MyString::scan(std::istream& is)
{
	const int block = 0x100;
	delete[] data;
	data = new char[block];
	char currentSymbol;
	int currentSize = 0;

	is.get(currentSymbol);
	while (!is.eof() && !isspace((unsigned char)currentSymbol))
	{
		data[currentSize++] = currentSymbol;
		is.get(currentSymbol);
		if (currentSize % block == 0)
		{
			char *newData = new char[currentSize + block];
			for (int i = 0; i < currentSize; ++i)
				newData[i] = data[i];

			delete[] data;
			data = newData;
		}
	}
	data[currentSize++] = 0;
	size = currentSize;
}
void MyString::fscan(FILE *fin)
{
	const int block = 0x100;
	delete[] data;
	data = new char[block];
	unsigned char currentSymbol;
	int currentSize = 0;

	currentSymbol = fgetc(fin);
	while (!isspace(currentSymbol) && !feof(fin))
	{
		data[currentSize++] = currentSymbol;
		currentSymbol = fgetc(fin);
		if (currentSize % block == 0)
		{
			char *newData = new char[currentSize + block];
			for (int i = 0; i < currentSize; ++i)
				newData[i] = data[i];

			delete[] data;
			data = newData;
		}
	}
	data[currentSize++] = 0;
	size = currentSize;
}

bool MyString::fgetline(FILE * fin)
{
	const int block = 0x100;
	delete[] data;
	data = new char[block];
	unsigned char currentSymbol;
	int currentSize = 0;

	currentSymbol = fgetc(fin);
	while (!feof(fin) && currentSymbol != '\r' && currentSymbol != '\n')
	{
		data[currentSize++] = currentSymbol;
		currentSymbol = fgetc(fin);
		if (currentSize % block == 0)
		{
			char *newData = new char[currentSize + block];
			for (int i = 0; i < currentSize; ++i)
				newData[i] = data[i];

			delete[] data;
			data = newData;
		}
	}
	data[currentSize++] = 0;
	size = currentSize;
	return (bool)feof(fin);
}


bool MyString::operator==(const char* other)const
{
	return strncmp(data, other, size) == 0;
}
bool MyString::operator!=(const char* other)const
{
	return strncmp(data, other, size) != 0;
}
void MyString::doForEach(void(*f)(char&))
{
	for (size_t i = 0; i < size; ++i)
		f(data[i]);
}
void MyString::doForEach(char(*f)(char))
{
	for (size_t i = 0; i < size; ++i)
		data[i] = f(data[i]);
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	for (size_t i = 0; i < str.getLength(); ++i)
		os << str[i];
	return os;
}
std::istream& operator>>(std::istream& is, MyString& str)
{
	str.scan(is);
	return is;
}
std::string& operator>>(std::string& is, MyString& str)
{
	str = is;
	return is;
}
MyString MyString::operator=(const char *other)
{
	delete[] data;
	data = new char[size = strlen(other) + 1];
	char *ptrThis = data;

	while (*ptrThis++ = *other++)
		;
	data[size - 1] = 0;

	return *this;
}
MyString MyString::operator=(const std::string other)
{
	delete[] data;
	data = new char[size = other.size() + 1];
	char *ptrThis = data;
	for (size_t i = 0; i < other.size(); ++i)
		*ptrThis++ = other[i];
	data[size - 1] = 0;

	return *this;
}

MyString MyString::operator=(const MyString& other)
{
	if (this == &other)
		return *this;
	delete[] data;
	data = new char[size = other.getLength() + 1];
	char *ptrThis = data;
	for (size_t i = 0; i < other.getLength(); ++i)
		*ptrThis++ = other[i];
	data[size - 1] = 0;

	return *this;
}
size_t MyString::getLength()const
{
	return size - 1;
}


MyString& MyString::operator += (const char *str)
{
	while (*str)
		*this += *(str++);
	return *this;
}
MyString& MyString::operator += (const MyString& other)
{
	return *this += (const char *)other;
}
MyString MyString::operator + (const MyString& other)
{
	MyString result(*this);

	result += other;

	return result;
}
char MyString::operator[](size_t ind) const
{
	return data[ind];
}
MyString MyString::getSubStr(size_t ind_start, size_t ind_last) const
{
	if (ind_start >= getLength() || ind_start > ind_last)
		return "";
	if(ind_last >= getLength())
		ind_last = getLength() - 1;
	MyString result;
	for (size_t i = ind_start; i <= ind_last; ++i)
		result += data[i];

	return result;
}
MyString MyString::GetStringFromNumber(__int64 num, __int64 min_width, char front)
{
	if (min_width <= 0)
	{
		if (num == 0)
			return "0";

		MyString result;
		bool add_minus = (num < 0);
		if (num < 0)
			num = -num;
		while (num)
		{
			result = MyString((char)(num % 10 + '0')) + result;
			num /= 10;
		}
		if (add_minus)
			result = MyString('-') + result;
		return result;
	}

	MyString temp = GetStringFromNumber(abs(num), -1);
	if (num >= 0)
	{
		while (temp.getLength() < (size_t)min_width)
			temp = MyString(front) + temp;
		return temp;
	}
	else
	{
		while (temp.getLength() + 1 < (size_t)min_width)
			temp = MyString(front) + temp;
		temp = MyString('-') + temp;
		return temp;
	}
}

MyString MyString::GetStringFromNumber(BigInteger num, __int64 min_width, char front)
{
	if (min_width <= 0)
	{
		if (num == 0)
			return "0";

		MyString result;
		bool add_minus = (num < 0);
		if (num < 0)
			num = -num;

		while (num)
		{
			result = MyString((char)(num.getDigitFromLast(0) + '0')) + result;
			num = num.div10();
		}
		if (add_minus)
			result = MyString('-') + result;

		return result;
	}

	MyString temp = GetStringFromNumber(num.module(), -1);
	if (num >= 0)
	{
		while (temp.getLength() < (size_t)min_width)
			temp = MyString(front) + temp;
		return temp;
	}
	else
	{
		while (temp.getLength() + 1 < (size_t)min_width)
			temp = MyString(front) + temp;

		if (front != ' ')
			temp = MyString('-') + temp;
		else
		{
			temp = MyString(' ') + temp;
			char * c = &temp.data[temp.getLength() - 1];
			while (c != temp.data && *c != ' ')
				--c;
			if (*c == ' ')
				*c = '-';
			else
				temp = MyString('-') + temp;
		}

		return temp;
	}
}
