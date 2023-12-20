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

#include <MyLib\MyException.hpp>

#ifndef NO_USE_SP
#ifdef SP
#error
#endif
#define SP SmartPointer
#endif

template<typename T>
class SmartPointer
{
private:
	T * data;
	size_t *counter;
public:
	T * _GetData() const { return data; }
	size_t * _GetCounter() const{ return counter; }
	SmartPointer()
	{
		data = nullptr;
		counter = new size_t(0);
	}
	SmartPointer(T * p)
	{
		data = p;
		counter = new size_t(p ? 1 : 0);
	}
	SmartPointer(const SmartPointer & other)
	{
		data = other.data;
		if (data)
		{
			counter = other.counter;
			++*counter;
		}
		else
			counter = new size_t(0);
	}
	template<typename D>
	SmartPointer(const SmartPointer<D> & other)
	{
		data = other._GetData();
		if (data)
		{
			counter = other._GetCounter();
			++*counter;
		}
		else
			counter = new size_t(0);
	}
	SmartPointer& operator =(const SmartPointer & other)
	{
		if (this == &other || data == other.data)
			return *this;
		if (*counter)
		{
			--*counter;
			if (*counter == 0)
			{
				delete data;
				delete counter;
			}
		}
		if (data == nullptr)
			delete counter;
		data = other.data;
		if (data)
		{
			counter = other.counter;
			++*counter;
		}
		else
			counter = new size_t(0);
		return *this;
	}
	template<typename D>
	SmartPointer& operator =(const SmartPointer<D> & other)
	{
		if (*this == other)
			return *this;
		if (*counter)
		{
			--*counter;
			if (*counter == 0)
			{
				delete data;
				delete counter;
			}
		}
		if (data == nullptr)
			delete counter;
		data = other._GetData();
		if (data)
		{
			counter = other._GetCounter();
			++*counter;
		}
		else
			counter = new size_t(0);
		return *this;
	}
	SmartPointer& operator =(T * other)
	{
		if (data == other)
			return *this;
		if (*counter)
		{
			--*counter;
			if (*counter == 0)
				delete data;
		}
		data = other;
		if (*counter)
			counter = new size_t();
		*counter = other ? 1 : 0;
		return *this;
	}

	T & operator *()
	{
		if (data == nullptr)
			throw MyException() << "\nError in\nT & SmartPointer::operator *() in\n" <<
			"FILE: " << __FILE__ << "\n" << "LINE: " << __LINE__ << "\n";
		return *data;
	}
	T * operator ->()
	{
		if (data == nullptr)
			throw MyException() << "\nError in\nT * SmartPointer::operator ->() in\n" <<
			"FILE: " << __FILE__ << "\n" << "LINE: " << __LINE__ << "\n";
		return data;
	}
	const T & operator *()const
	{
		if (data == nullptr)
			throw MyException() << "\nError in\nT & SmartPointer::operator *() in\n" <<
			"FILE: " << __FILE__ << "\n" << "LINE: " << __LINE__ << "\n";
		return *data;
	}
	const T * operator ->()const
	{
		if (data == nullptr)
			throw MyException() << "\nError in\nT * SmartPointer::operator ->() in\n" <<
			"FILE: " << __FILE__ << "\n" << "LINE: " << __LINE__ << "\n";
		return data;
	}
	bool operator ==(const SmartPointer & other) const
	{
		return data == other.data;
	}
	template<typename D>
	bool operator ==(const SmartPointer<D> & other) const
	{
		return other ? data == other.operator->() : !data;
	}
	bool operator ==(const T * other) const
	{
		return data == other;
	}
	bool operator ==(const nullptr_t & other) const
	{
		return data == other;
	}
	bool operator !=(const SmartPointer & other) const
	{
		return data != other.data;
	}
	template<typename D>
	bool operator !=(const SmartPointer<D> & other) const
	{
		return other ? data != other.operator->() : data;
	}
	bool operator !=(const T * other) const
	{
		return data != other;
	}
	bool operator !=(const nullptr_t & other) const
	{
		return data != other;
	}
	operator bool()const
	{
		return data != nullptr;
	}

	~SmartPointer()
	{
		if (data != nullptr)
			--*counter;
		if (*counter == 0)
		{
			delete data;
			delete counter;
		}
	}
};