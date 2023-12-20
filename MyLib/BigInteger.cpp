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

#include "BigInteger.hpp"

using namespace std;

BigInteger::BigInteger()
{
	sign = '+';
	data.push_back(0);
}
BigInteger::BigInteger(int value)
{
	if(value < 0)
		sign = '-';
	else
		sign = '+';

	if(value == 0)
	{
		data.push_back(0);
		return;
	}

	value = ABS(value);
	while(value)
	{
		data.push_back(value % 10);
		value /= 10;
	}
}
BigInteger::BigInteger(unsigned int value)
{
	sign = '+';

	if(value == 0)
	{
		data.push_back(0);
		return;
	}
	while(value)
	{
		data.push_back(value % 10);
		value /= 10;
	}
}
BigInteger::BigInteger(__int64 value)
{
	if(value < 0)
		sign = '-';
	else
		sign = '+';

	if(value == 0)
	{
		data.push_back(0);
		return;
	}

	value = ABS(value);
	while(value)
	{
		data.push_back(value % 10);
		value /= 10;
	}
}
BigInteger::BigInteger(unsigned __int64 value)
{
	sign = '+';

	if(value == 0)
	{
		data.push_back(0);
		return;
	}
	while(value)
	{
		data.push_back(value % 10);
		value /= 10;
	}
}
BigInteger::BigInteger(const char *value)
{
	size_t currentlength = strlen(value);
	__int64 position = (__int64)currentlength-1;
	int min_pos;

	if(currentlength)
	{
		min_pos = value[0] == '-' ? 1 : 0;
		sign = value[0] == '-' ? '-' : '+';
		if(min_pos == 1)
			currentlength--;
	}
	else
		min_pos = 0;

	if(currentlength == 0)
	{
		data.push_back(0);
		sign = '+';
		return;
	}

	while(position >= min_pos)
		data.push_back(value[position--]-'0');
}

BigInteger::BigInteger(const BigInteger& other)
{
	sign = other.sign;
	data = other.data;
}
BigInteger BigInteger::operator=(const BigInteger& other)
{
	if(this == &other)
		return *this;
	sign = other.sign;
	data.clear();
	data = other.data;
	return *this;
}


void BigInteger::print(ostream& os)const
{

	if(sign == '-')
		os << '-';
	for(vector<__int8>::const_reverse_iterator crit = data.crbegin(); crit != data.crend(); ++crit)
		os << (int)*crit;
}
void BigInteger::println(ostream& os)const
{
	print(os);
	os << endl;
}


inline BigInteger BigInteger::operator+()const
{
	return *this;
}
BigInteger BigInteger::operator+=(const BigInteger& other)
{
	bool mem = 0;
	size_t position;

	if(sign == other.sign)
	{
		for(position = 0; position < MIN(data.size(), other.data.size()); position++)
		{
			bool newMemory = (data[position] + other.data[position] + mem) >= 10;
			data[position] = (data[position] + other.data[position] + mem)%10;
			mem = newMemory;
		}
		if(data.size() > other.data.size())
		{
			for(position = other.data.size(); position < data.size(); position++)
			{
				bool newMemory = (data[position] + mem) >= 10;
				data[position] = (data[position] + mem)%10;
				mem = newMemory;
			}
			if(mem)
			{
				data.push_back(1);
			}
			return *this;
		}/* if(length > other.length) */

		for(position = data.size(); position < other.data.size(); position++)
		{
			bool newMemory = (other.data[position] + mem) >= 10;
			data.push_back((other.data[position] + mem)%10);
			mem = newMemory;
		}
		if(mem)
		{
			data.push_back(1);
		}
		return *this;
	}/* if(sign == other.sign) */

	size_t newlength = MAX(data.size(), other.data.size());
	
	if(isMoreABS(other))
	{	
		for(position = 0; position < other.data.size(); position++)
		{
			data[position] = (data[position] - other.data[position] - mem);
			mem = data[position] < 0 ? 1 : 0;
			if(data[position] < 0)
				data[position] += 10;
		}
		for(position = other.data.size(); position < newlength; position++)
		{
			data[position] = (data[position] - mem);
			mem = data[position] < 0 ? 1 : 0;
			if(data[position] < 0)
				data[position] += 10;
		}

		while(data[position-1] == 0 && (position-- -1)>0)
			data.pop_back();

		return *this;
	}/* if(isMoreABS(other)) */
	
	sign = other.sign;

	for(position = 0; position < data.size(); position++)
	{
		data[position] = (other.data[position] - data[position] - mem);
		mem = data[position] < 0 ? 1 : 0;
		if(data[position] < 0)
			data[position] += 10;
	}
	for(position = data.size(); position < other.data.size(); position++)
	{
		data.push_back(other.data[position] - mem);
		mem = data[position] < 0 ? 1 : 0;
		if(data[position] < 0)
			data[position] += 10;
	}
	while(data[position-1] == 0 && (position-- -1)>0)
		data.pop_back();

	if(data.size() == 1 && data[0] == 0)
		sign = '+';

	return *this;
}
BigInteger BigInteger::operator+(const BigInteger& other) const
{
	BigInteger result(*this);
	result += other;
	return result;
}

BigInteger BigInteger::operator-()const
{
	BigInteger result(*this);

	if(result.data.size() == 1 && result.data[0] == 0)
		return result;
	result.sign = result.sign == '+' ? '-' : '+';
	return result;
}
BigInteger BigInteger::operator-=(const BigInteger& other)
{
	BigInteger temp(-other);
	*this += temp;
	return *this;
}
BigInteger BigInteger::operator-(const BigInteger& other) const
{
	BigInteger result(*this);
	result -= other;
	return result;
}

BigInteger BigInteger::operator*=(const BigInteger& other)
{

#define USE_KARATSUBA
#define MIN_LENGTH_FOR_KARATSUBA 0x100
//A * B = A0 * B0    + (( A0 + A1 ) * ( B0 + B1 ) — A0   * B0   —   A1 * B1 ) * 10^m +    A1 * B1   * 10^(2 * m)
//           ^               ^      ^      ^      ^      ^      ^      ^      ^      ^       ^      ^                   
//           p1(1)   s3(12)  s1(2)  p2(4)  s2(3)  p2(6)  p1(1)  p2(7)  p3(5)  p2(8)  s3(11)  p4(9)  p4(10)  
	BigInteger a0, b0, a1, b1, p1, p2, p3, p4, s1, s2, s3, result;
	size_t posa, posb, m, max_pos, k;

	

	if((data.size() == 1 && data[0] == 0) || (other.data.size() == 1 && other.data[0] == 0))
	{
		*this = 0;
		return *this;
	}


	

#ifdef USE_KARATSUBA
	if(data.size() < MIN_LENGTH_FOR_KARATSUBA || other.data.size() < MIN_LENGTH_FOR_KARATSUBA)
	{
#endif
		for(size_t i = 0; i < data.size()+other.data.size(); ++i)
			result.data.push_back(0);

		max_pos = 0;
		for(posa = 0; posa < data.size(); posa++)
		{
			for(posb = 0; posb < other.data.size(); posb++)
			{
				if(max_pos < posa+posb+1)
					max_pos = posa+posb+1;
				result.data[posa+posb] += data[posa]*other.data[posb];

				if(result.data[posa+posb] >= 10)
				{
					if(max_pos < posa+posb+1+1)
						max_pos++;

					k = result.data[posa+posb]/10;
					result.data[posa+posb] %= 10;
					result.data[posa+posb+1]+=k;
				}
			}
		}

		while(result.data.size() && (result.data[result.data.size() - 1] == 0))
			result.data.pop_back();
		if(result.data.size() == 0)
			result.data.push_back(0);
		if(sign == other.sign)
			result.sign = '+';
		else
			result.sign = '-';
		
		*this = result;
		return *this;
#ifdef USE_KARATSUBA
	}




	m = MAX(data.size()/2, other.data.size()/2);
	if(data.size() <= m)
	{
		a0.createFromVector_reverse(data, data.size(), 0);//a0.createStrSizeFlip(data, data.size());
		a1 = "";
	}
	if(other.data.size() <= m)
	{
		b0.createFromVector_reverse(other.data, other.data.size(), 0);//b0.createStrSizeFlip(other.data, other.data.size());
		b1 = "";
	}
	if(data.size() > m)
	{
		a0.createFromVector_reverse(data, m, 0);//a0.createStrSizeFlip(data, m);
		a1.createFromVector_reverse(data, data.size() - m, m);//a1.createStrSizeFlip(&data[m], data.size() - m);
	}
	if(other.data.size() > m)
	{
		b0.createFromVector_reverse(other.data, m, 0);//b0.createStrSizeFlip(other.data, m);
		b1.createFromVector_reverse(other.data, other.data.size() - m, m);//b1.createStrSizeFlip(&other.data[m], other.data.size() - m);
	}
	

//A * B = A0 * B0    + (( A0 + A1 ) * ( B0 + B1 ) — A0   * B0   —   A1 * B1 ) * 10^m +    A1 * B1   * 10^(2 * m)
//           ^       ^       ^      ^      ^      ^      ^      ^      ^      ^      ^       ^      ^                   
//           p1(1)   s3(12)  s1(2)  p2(4)  s2(3)  p2(6)  p1(1)  p2(7)  p3(5)  p2(8)  s3(11)  p4(9)  p4(10)  
	
	
	p1 = a0 * b0;//mult_bi(&p1, a0, b0);
	s1 = a0 + a1;//summ_bi(&s1, a0, a1);
	s2 = b0 + b1;//summ_bi(&s2, b0, b1);
	p2 = s1 * s2;//mult_bi(&p2, s1, s2);
	p3 = a1 * b1;//mult_bi(&p3, a1, b1);
	p1.sign = p3.sign = '-';	
	p2 += p1;//add_bi(&p2, p1);
	p2 += p3;//add_bi(&p2, p3);
	p2.mulpow10(m);//pow10_bi(&p2, m);
	p4 = a1 * b1;//mult_bi(&p4, a1, b1);
	p4.mulpow10(2*m);//pow10_bi(&p4, 2*m);
	s3 = p2 + p4;//summ_bi(&s3, p2, p4);

	p1.sign = '+';
	s3 += p1;//add_bi(&s3, p1);


	result = s3;//assignment_bi(result, s3);
	if(sign == other.sign)
		result.sign = '+';
	else
		result.sign = '-';
#endif /* USE_KARATSUBA */
	*this = result;
	return *this;
}
BigInteger BigInteger::operator*(const BigInteger& other) const
{
	BigInteger result(*this);
	result *= other;
	return result;
}

BigInteger BigInteger::operator/=(const BigInteger& other)
{
	BigInteger body, head_help, head, subtrahend, currentNum, addedResult, numInAddedResult_head, numInAddedResult_body, result;
	BigInteger otherABS;
	size_t cnt_bodies, cnt_zeroes, ui;

	if(other.isMoreABS(*this))
	{
		*this = 0;
		return *this;
	}

	

	currentNum = *this;
	otherABS = other;
	currentNum.sign = '+';
	otherABS.sign = '+';
	result = 0;
	

	numInAddedResult_body = 1;//create_bi(&numInAddedResult_body, 1);
	body = other;//assignment_bi(&body, other);
	do
	{
		++numInAddedResult_body;//add_bi(&numInAddedResult_body, one);
		body += other;//add_bi(&body, other);
	}while(body.data.size() <= other.data.size());

	body -= other;//subt_bi(&body, other);
	--numInAddedResult_body;//subt_bi(&numInAddedResult_body, one);

	for(ui = numInAddedResult_body.data.size(); ui < body.data.size(); ui++)
	{
		numInAddedResult_body.data.push_back(0);
	}




	while(currentNum.data.size() > body.data.size())
	{


		numInAddedResult_head = 0;//create_bi(&numInAddedResult_head, 0);

		
		head_help.createFromVector_reverse(currentNum.data,  body.data.size()+1, currentNum.data.size() - (body.data.size()+1));//createStrSizeFlip_bi(&head_help, &currentNum.data[currentNum.length - (body.length+1)], body.length+1);


		head = 0;//create_bi(&head, 0);
		do
		{
			++numInAddedResult_head;//add_bi(&numInAddedResult_head, one);
			head += other;//add_bi(&head, other);
		}while(head_help.isMoreABS(head));//while(isMoreABS_bi(head_help, head));

		head -= other;//subt_bi(&head, other);
		--numInAddedResult_head;//subt_bi(&numInAddedResult_head, one);
		


		cnt_bodies = (currentNum.data.size() - head_help.data.size()) / body.data.size();
		



		cnt_zeroes = currentNum.data.size() - cnt_bodies*body.data.size() - head_help.data.size();
		

		addedResult = 1;//create_bi(&addedResult, 1);
		if(cnt_zeroes)
			addedResult.mulpow10(cnt_zeroes);//pow10_bi(&addedResult, cnt_zeroes);
		addedResult.data.pop_back();

		for(ui = 0; ui < cnt_bodies; ui++)
		{
			for(size_t i = 0; i < numInAddedResult_body.data.size(); ++i)
				addedResult.data.push_back(numInAddedResult_body.data[i]);
			///memcpy(&addedResult.data[addedResult.length], numInAddedResult_body.data, numInAddedResult_body.length);
			//addedResult.length += body.length;
		}
		for(size_t i = 0; i < numInAddedResult_head.data.size(); ++i)
			addedResult.data.push_back(numInAddedResult_head.data[i]);
		//memcpy(&addedResult.data[addedResult.length], numInAddedResult_head.data, numInAddedResult_head.length);
		//addedResult.length += numInAddedResult_head.length;



		subtrahend = 1;//create_bi(&subtrahend, 1);
		if(cnt_zeroes)
			subtrahend.mulpow10(cnt_zeroes);//pow10_bi(&subtrahend, cnt_zeroes);
		subtrahend.data.pop_back();

		for(ui = 0; ui < cnt_bodies; ui++)
		{
			for(size_t i = 0; i < body.data.size(); ++i)
				subtrahend.data.push_back(body.data[i]);
			//memcpy(&subtrahend.data[subtrahend.length], body.data, body.length);
			//subtrahend.length += body.length;
		}
		for(size_t i = 0; i < head.data.size(); ++i)
			subtrahend.data.push_back(head.data[i]);
		//memcpy(&subtrahend.data[subtrahend.length], head.data, head.length);
		//subtrahend.length += head.length;



		result += addedResult;//add_bi(result, addedResult);
		currentNum -= subtrahend;//subt_bi(&currentNum, subtrahend);
	}


	while(!otherABS.isMoreABS(currentNum))//while(!isMoreABS_bi(otherABS, currentNum))
	{
		currentNum -= otherABS;//subt_bi(&currentNum, otherABS);
		++result;//add_bi(result, one);
	}

	if(this->sign == other.sign)
		result.sign = '+';
	else
		result.sign = '-';

	//freeV_bi(&body, &numInAddedResult_body, &currentNum, &one, &otherABS, NULL);

	*this = result;
	return *this;

}
BigInteger BigInteger::operator/(const BigInteger& other) const
{
	BigInteger result(*this);
	result /= other;
	return result;
}

BigInteger BigInteger::operator%=(const BigInteger& other)
{
	BigInteger body, head_help, head, subtrahend, currentNum, addedResult, numInAddedResult_head, numInAddedResult_body, result;
	BigInteger otherABS;
	size_t cnt_bodies, cnt_zeroes, ui;

	if(other.isMoreABS(*this))
		return *this;

	

	currentNum = *this;
	otherABS = other;
	currentNum.sign = '+';
	otherABS.sign = '+';
	result = 0;
	

	numInAddedResult_body = 1;//create_bi(&numInAddedResult_body, 1);
	body = other;//assignment_bi(&body, other);
	do
	{
		++numInAddedResult_body;//add_bi(&numInAddedResult_body, one);
		body += other;//add_bi(&body, other);
	}while(body.data.size() <= other.data.size());

	body -= other;//subt_bi(&body, other);
	--numInAddedResult_body;//subt_bi(&numInAddedResult_body, one);

	for(ui = numInAddedResult_body.data.size(); ui < body.data.size(); ui++)
	{
		numInAddedResult_body.data.push_back(0);
	}




	while(currentNum.data.size() > body.data.size())
	{


		numInAddedResult_head = 0;//create_bi(&numInAddedResult_head, 0);

		
		head_help.createFromVector_reverse(currentNum.data,  body.data.size()+1, currentNum.data.size() - (body.data.size()+1));//createStrSizeFlip_bi(&head_help, &currentNum.data[currentNum.length - (body.length+1)], body.length+1);


		head = 0;//create_bi(&head, 0);
		do
		{
			++numInAddedResult_head;//add_bi(&numInAddedResult_head, one);
			head += other;//add_bi(&head, other);
		}while(head_help.isMoreABS(head));//while(isMoreABS_bi(head_help, head));

		head -= other;//subt_bi(&head, other);
		--numInAddedResult_head;//subt_bi(&numInAddedResult_head, one);
		


		cnt_bodies = (currentNum.data.size() - head_help.data.size()) / body.data.size();
		



		cnt_zeroes = currentNum.data.size() - cnt_bodies*body.data.size() - head_help.data.size();
		

		addedResult = 1;//create_bi(&addedResult, 1);
		if(cnt_zeroes)
			addedResult.mulpow10(cnt_zeroes);//pow10_bi(&addedResult, cnt_zeroes);
		addedResult.data.pop_back();

		for(ui = 0; ui < cnt_bodies; ui++)
		{
			for(size_t i = 0; i < numInAddedResult_body.data.size(); ++i)
				addedResult.data.push_back(numInAddedResult_body.data[i]);
			///memcpy(&addedResult.data[addedResult.length], numInAddedResult_body.data, numInAddedResult_body.length);
			//addedResult.length += body.length;
		}
		for(size_t i = 0; i < numInAddedResult_head.data.size(); ++i)
			addedResult.data.push_back(numInAddedResult_head.data[i]);
		//memcpy(&addedResult.data[addedResult.length], numInAddedResult_head.data, numInAddedResult_head.length);
		//addedResult.length += numInAddedResult_head.length;



		subtrahend = 1;//create_bi(&subtrahend, 1);
		if(cnt_zeroes)
			subtrahend.mulpow10(cnt_zeroes);//pow10_bi(&subtrahend, cnt_zeroes);
		subtrahend.data.pop_back();

		for(ui = 0; ui < cnt_bodies; ui++)
		{
			for(size_t i = 0; i < body.data.size(); ++i)
				subtrahend.data.push_back(body.data[i]);
			//memcpy(&subtrahend.data[subtrahend.length], body.data, body.length);
			//subtrahend.length += body.length;
		}
		for(size_t i = 0; i < head.data.size(); ++i)
			subtrahend.data.push_back(head.data[i]);
		//memcpy(&subtrahend.data[subtrahend.length], head.data, head.length);
		//subtrahend.length += head.length;



		result += addedResult;//add_bi(result, addedResult);
		currentNum -= subtrahend;//subt_bi(&currentNum, subtrahend);
	}


	while(!otherABS.isMoreABS(currentNum))//while(!isMoreABS_bi(otherABS, currentNum))
	{
		currentNum -= otherABS;//subt_bi(&currentNum, otherABS);
		++result;//add_bi(result, one);
	}

	currentNum.sign = sign;
	*this = currentNum;
	if(data.size() == 1 && data[0] == 0)
		sign = '+';
	return *this;

}
BigInteger BigInteger::operator%(const BigInteger& other) const
{
	BigInteger result(*this);
	result %= other;
	return result;
}

BigInteger BigInteger::operator++()
{
	*this += 1;
	return *this;
}
BigInteger BigInteger::operator++(int)
{
	BigInteger temp(*this);
	*this += 1;
	return temp;
}
BigInteger BigInteger::operator--()
{
	*this -= 1;
	return *this;
}
BigInteger BigInteger::operator--(int)
{
	BigInteger temp(*this);
	*this -= 1;
	return temp;
}

bool BigInteger::operator==(const BigInteger& other)const
{
	if(sign != other.sign)
		return false;
	if(data.size() != other.data.size())
		return false;
	
	for(vector<__int8>::const_iterator 
		ritThis = data.cbegin(),
		ritOther= other.data.cbegin();
		ritThis != data.cend();
		++ritThis,
		++ritOther)
	{
		if(*ritThis != *ritOther)
			return false;
	}

	return true;

}
bool BigInteger::operator!=(const BigInteger& other)const
{
	if(sign != other.sign)
		return true;
	if(data.size() != other.data.size())
		return true;
	
	for(vector<__int8>::const_iterator 
		ritThis = data.cbegin(),
		ritOther= other.data.cbegin();
		ritThis != data.cend();
		++ritThis,
		++ritOther)
	{
		if(*ritThis != *ritOther)
			return true;
	}

	return false;

}
bool BigInteger::operator>=(const BigInteger& other)const
{
	if(sign == '-' && other.sign == '+')
		return false;
	if(sign == '+' && other.sign == '-')
		return true;

	if(sign == '+')
	{
		if(data.size() > other.data.size())
			return true;
		if(data.size() < other.data.size())
			return false;
	
		for(vector<__int8>::const_reverse_iterator 
			ritThis = data.crbegin(),
			ritOther= other.data.crbegin();
			ritThis != data.crend();
			++ritThis,
			++ritOther)
		{
			if(*ritThis < *ritOther)
				return false;
			if(*ritThis > *ritOther)
				return true;
		}
	}
	if(sign == '-')
	{
		if(data.size() < other.data.size())
			return true;
		if(data.size() > other.data.size())
			return false;
	
		for(vector<__int8>::const_reverse_iterator 
			ritThis = data.crbegin(),
			ritOther= other.data.crbegin();
			ritThis != data.crend();
			++ritThis,
			++ritOther)
		{
			if(*ritThis > *ritOther)
				return false;
			if(*ritThis < *ritOther)
				return false;
		}
	}
	return true;
}
bool BigInteger::operator>(const BigInteger& other)const
{
	if(sign == '-' && other.sign == '+')
		return false;
	if(sign == '+' && other.sign == '-')
		return true;

	if(sign == '+')
	{
		if(data.size() > other.data.size())
			return true;
		if(data.size() < other.data.size())
			return false;
	
		for(vector<__int8>::const_reverse_iterator 
			ritThis = data.crbegin(),
			ritOther= other.data.crbegin();
			ritThis != data.crend();
			++ritThis,
			++ritOther)
		{
			if(*ritThis < *ritOther)
				return false;
			if(*ritThis > *ritOther)
				return true;
		}
	}
	if(sign == '-')
	{
		if(data.size() < other.data.size())
			return true;
		if(data.size() > other.data.size())
			return false;
	
		for(vector<__int8>::const_reverse_iterator 
			ritThis = data.crbegin(),
			ritOther= other.data.crbegin();
			ritThis != data.crend();
			++ritThis,
			++ritOther)
		{
			if(*ritThis > *ritOther)
				return false;
			if(*ritThis < *ritOther)
				return true;
		}
	}
	return false;

}
bool BigInteger::operator<=(const BigInteger& other)const
{
	if(sign == '-' && other.sign == '+')
		return true;
	if(sign == '+' && other.sign == '-')
		return false;

	if(sign == '+')
	{
		if(data.size() > other.data.size())
			return false;
		if(data.size() < other.data.size())
			return true;
	
		for(vector<__int8>::const_reverse_iterator 
			ritThis = data.crbegin(),
			ritOther= other.data.crbegin();
			ritThis != data.crend();
			++ritThis,
			++ritOther)
		{
			if(*ritThis > *ritOther)
				return false;
			if(*ritThis < *ritOther)
				return true;
		}
	}
	if(sign == '-')
	{
		if(data.size() < other.data.size())
			return false;
		if(data.size() > other.data.size())
			return true;
	
		for(vector<__int8>::const_reverse_iterator 
			ritThis = data.crbegin(),
			ritOther= other.data.crbegin();
			ritThis != data.crend();
			++ritThis,
			++ritOther)
		{
			if(*ritThis < *ritOther)
				return false;
			if(*ritThis > *ritOther)
				return true;
		}
	}
	return true;
}
bool BigInteger::operator<(const BigInteger& other)const
{
	if(sign == '-' && other.sign == '+')
		return true;
	if(sign == '+' && other.sign == '-')
		return false;

	if(sign == '+')
	{
		if(data.size() > other.data.size())
			return false;
		if(data.size() < other.data.size())
			return true;
	
		for(vector<__int8>::const_reverse_iterator 
			ritThis = data.crbegin(),
			ritOther= other.data.crbegin();
			ritThis != data.crend();
			++ritThis,
			++ritOther)
		{
			if(*ritThis > *ritOther)
				return false;
			if(*ritThis < *ritOther)
				return true;
		}
	}
	if(sign == '-')
	{
		if(data.size() < other.data.size())
			return false;
		if(data.size() > other.data.size())
			return true;
	
		for(vector<__int8>::const_reverse_iterator 
			ritThis = data.crbegin(),
			ritOther= other.data.crbegin();
			ritThis != data.crend();
			++ritThis,
			++ritOther)
		{
			if(*ritThis < *ritOther)
				return false;
			if(*ritThis > *ritOther)
				return true;
		}
	}
	return false;

}

BigInteger::operator bool()const
{
	return !(sign == '+' && data.size() == 1 && data[0] == 0);
}
BigInteger BigInteger::div2()
{
	BigInteger help;
	int currentNum;
	size_t pos;

	help.sign = this->sign;
	help.data.clear();
	for(pos = 0; pos < this->data.size() - (this->data.size()%2); pos += 2)
	{
		currentNum = this->data[pos+1]*10 + this->data[pos];
		if(pos > 0 && currentNum%2)
		{
			help.data[pos-1] += 5;
			currentNum--;
		}
		currentNum /= 2;
		help.data.push_back(currentNum % 10);
		help.data.push_back(currentNum / 10);
		
	}
	if(this->data.size()%2)
	{
		currentNum = this->data[pos];
		if(pos > 0 && currentNum%2)
		{
			help.data[pos-1] += 5;
			currentNum--;
		}
		currentNum /= 2;
		help.data.push_back(currentNum % 10);
		help.data.push_back(currentNum / 10);
	}

	while(help.data.size() && help.data.back() == 0)
		help.data.pop_back();
	if(help.data.size() == 0)
		help.data.push_back(0);
	
	
	*this = help;
	if(this->data.size() == 1 && this->data[0] == 0)
		this->sign = '+';
	return *this;
}
BigInteger BigInteger::gcd(const BigInteger& other)const
{
	BigInteger a1, a11, b11, t, result;
	int resta, restb;

	a11 = *this;
	b11 = other;
	a11.sign = b11.sign = '+';
	t = 1;
	while(1)
	{
		if(a11 == b11)
		{
			result = t * a11;
			break;
		}
		if(!a11)
		{
			result = t * b11;
			break;
		}
		if(!b11)
		{
			result = t * a11;
			break;
		}
		if(a11==(BigInteger)1)
		{
			result = t;
			break;
		}
		if(b11 == (BigInteger)1)
		{
			result = t;
			break;
		}

		resta = a11.data[0] % 2;
		restb = b11.data[0] % 2;
		
		if(!resta&&!restb)
		{
			t *= 2;
			a11.div2();
			b11.div2();
			continue;
		}
		if(!resta)
		{
			a11.div2();
			continue;
		}
		if(!restb)
		{
			b11.div2();
			continue;
		}

		if(resta&&restb)
		{
			if(a11 > b11)
			{
				a1 = a11 - b11;
				a1.div2();
			}
			else
			{
				a1 = b11 - a11;
				a1.div2();
			}


			b11 = a11;
			a11 = a1;

			continue;
		}
	}

	return result;
}
BigInteger BigInteger::pow(const BigInteger& other)const
{
	BigInteger result(1);

	for(BigInteger i = 0; i < other; ++i)
	{
		result *= *this;
	}

	return result;
}
BigInteger BigInteger::pow(const unsigned __int64 exponent)const
{
	BigInteger result(1);

	for(unsigned __int64 i = 0; i < exponent; ++i)
	{
		result *= *this;
	}

	return result;
}
BigInteger BigInteger::pow(const signed __int64 exponent)const
{
	if(exponent < 0)
		return (BigInteger)(*this == (BigInteger)(1));
	BigInteger result(1);

	for(signed __int64 i = 0; i < exponent; ++i)
	{
		result *= *this;
	}

	return result;
}
BigInteger BigInteger::pow(const unsigned __int32 exponent)const
{
	BigInteger result(1);

	for(unsigned __int32 i = 0; i < exponent; ++i)
	{
		result *= *this;
	}

	return result;
}
BigInteger BigInteger::pow(const signed __int32 exponent)const
{
	if(exponent < 0)
		return (BigInteger)(*this == (BigInteger)(1));
	BigInteger result(1);
	for(signed __int32 i = 0; i < exponent; ++i)
	{
		result *= *this;
	}

	return result;
}

BigInteger BigInteger::qpow(unsigned __int64 exponent)const
{
	BigInteger result(1), help(*this);

	while(exponent)
	{
		if(exponent & 1)	
			result *= help;
		help *= help;
		exponent >>= 1;
	}

	return result;
}

BigInteger BigInteger::qpmod(const BigInteger& exponent, const BigInteger& module)const
{
	BigInteger help_exponent(exponent), result(1);
	vector<bool>e;

	while(help_exponent)
	{
		e.push_back(help_exponent.data[0] % 2 == 1);
		help_exponent.div2();
	}

	while(!e.empty())
	{
		result *= result;
		if(e.back())
			result *= *this;
		result %= module;
		e.pop_back();

	}
	result %= module;

	return result;
}


bool BigInteger::isMoreABS(const BigInteger& other) const
{
	__int64 pos;

	if(data.size() > other.data.size())
		return true;
	if(data.size() < other.data.size())
		return false;

	pos = data.size();
	while(--pos >= 0)
	{
		if(data[(size_t)pos] > other.data[(size_t)pos])
			return true;
		if(data[(size_t)pos] < other.data[(size_t)pos])
			return false;
	}
	return false;
}
void BigInteger::createFromVector_reverse(const vector<__int8>& _data, size_t length, size_t start)
{
	sign = '+';

	data.clear();
	for(size_t i = 0; i < length; ++i)
		data.push_back(_data[start + i]);
}
void BigInteger::mulpow10(size_t pow)
{
	__int64 pos;

	if(data.size() == 1 && data[0] == 0)
		return;

	for(size_t i = 0; i < pow; ++i)
		data.push_back(0);


	for(pos = data.size() - 1; pos >= pow; pos--)
		data[(size_t)pos] = data[(size_t)pos - pow];
	for(pos = pow-1; pos >= 0; pos--)
		data[(size_t)pos] = 0;
}
ostream& operator<<(ostream& os, const BigInteger& b)
{
	b.print(os);
	return os;
}
istream& operator>>(istream& is, BigInteger& b)
{
	MyString ms;
	ms.scan(is);
	b = (BigInteger)ms;
	return is;
}
BigInteger operator+(__int64 a, const BigInteger & b)
{
	return BigInteger(a) + b;
}
BigInteger operator+(unsigned __int64 a, const BigInteger & b)
{
	return BigInteger(a) + b;
}
BigInteger operator+(const char * a, const BigInteger & b)
{
	return BigInteger(a) + b;
}
BigInteger operator-(__int64 a, const BigInteger & b)
{
	return BigInteger(a) - b;
}
BigInteger operator-(unsigned __int64 a, const BigInteger & b)
{
	return BigInteger(a) - b;
}
BigInteger operator-(const char * a, const BigInteger & b)
{
	return BigInteger(a) - b;
}
BigInteger operator*(__int64 a, const BigInteger & b)
{
	return BigInteger(a) * b;
}
BigInteger operator*(unsigned __int64 a, const BigInteger & b)
{
	return BigInteger(a) * b;
}
BigInteger operator*(const char * a, const BigInteger & b)
{
	return BigInteger(a) * b;
}
BigInteger operator/(__int64 a, const BigInteger & b)
{
	return BigInteger(a) / b;
}
BigInteger operator/(unsigned __int64 a, const BigInteger & b)
{
	return BigInteger(a) / b;
}
BigInteger operator/(const char * a, const BigInteger & b)
{
	return BigInteger(a) / b;
}
BigInteger operator%(__int64 a, const BigInteger & b)
{
	return BigInteger(a) % b;
}
BigInteger operator%(unsigned __int64 a, const BigInteger & b)
{
	return BigInteger(a) % b;
}
BigInteger operator%(const char * a, const BigInteger & b)
{
	return BigInteger(a) % b;
}
BigInteger BigInteger::getRandom(bool reset)
{
	static BigInteger a;
	static bool flag_aWasInitialised = 0;
	BigInteger x, y, z;
	int step = 1;
	size_t i;

	if(reset)
	{
		flag_aWasInitialised = 0;
		return 0;
	}

	if(!flag_aWasInitialised)
	{
		a = "1000000000000000";
		flag_aWasInitialised = 1;
	}
	else
	{
		++a;
		if(a.length() == 11)
		{
			a = "1000000000000000";
		}
	}


	x = a;

	while(1)
	{
		if(step == 1)
		{
			y = x / 1000000000000000;
			++step;
		}
		if(step == 2)
		{
			z = x / 100000000000000;
			z %= 10;//subm_int_bi(&z, 10);
			step = 3 + z.data[0];
			continue;
		}
		if(step == 3)
		{
			if(x < 5000000000000000)
				x += 5000000000000000;
			++step;
		}
		if(step == 4)
		{
			x = x*x/(BigInteger(10)).pow(8)%(BigInteger(10)).pow(16);//solveExpression_bi(&x, 1, "(#B*#B/10^8)%10^16", x, x);
			++step;
		}
		if(step == 5)
		{
			x = x * 1001001001001001 %((BigInteger)10).pow(16);//solveExpression_bi(&x, 1, "(#B*1001001001001001)%10^16", x);
			++step;
		}
		if(step == 6)
		{
			if(x < 100000000000000)
				x += 9814055677777777;
			else
				x = 10000000000000000 - x;//subtRight_str_bi("10000000000000000", &x);
			++step;
		}
		if(step == 7)
		{
			x = (x%100000000)*100000000+x/100000000;//solveExpression_bi(&x, 1, "10^8*(#B%10^8)+#B/10^8", x, x);
			++step;
		}
		if(step == 8)
		{
			x = x * 1001001001001001 % 10000000000000000;//solveExpression_bi(&x, 1, "(#B*1001001001001001)%10^16", x);
			++step;
		}
		if(step == 9)
		{
			for(i = 0; i < x.length(); i++)
				x.data[i] -= (x.data[i] != 0);
			while(!x.data.back())
				x.data.pop_back();
			++step;
		}
		if(step == 10)
		{
			if(x < 100000000)
			{
				x = x*x+99999999;//solveExpression_bi(&x, 1, "#B*#B+99999999", x, x);
			}
			else
				x -= 99999999;//subt_int_bi(&x, 99999999);
			++step;
		}
		if(step == 11)
		{
			while(x < 1000000000000000)
				x *= 10;
			++step;
		}
		if(step == 12)
		{
			x = x*(x-1)/100000000%10000000000000000;//solveExpression_bi(&x, 1, "(#B*(#B-1)/10^8) % 10^16", x, x);
			++step;
		}
		if(step == 13)
		{
			if(y > 0)
			{
				--y;
				step = 2;
				continue;
			}

			return x;
		}
	}
}


inline size_t BigInteger::length()const
{
	return data.size();
}
signed __int64 BigInteger::lengthdiff()const{return (signed __int64)data.size();}
bool BigInteger::isSharedBy2()const{return data.back()%2 == 0;}

int BigInteger::getDigitFromLast(size_t position)const
{
	return data[position];
}
void BigInteger::setDigitFromLast(int digit, int position)
{
	if(digit >= 0 && digit <= 9)
		data[position] = digit;
}

BigInteger BigInteger::lead(const BigInteger& module)
{
	BigInteger k;

	while(*this < 0)
	{
		k = *this / module;
		k.sign = '+';
		if(!k)
			++k;
		k *= module;
		*this += k;
	}
	while(*this >= module)
	{
		k = *this / module;
		k.sign = '+';
		if(!k)
			++k;
		k *= module;
		*this -= k;
	}

	return *this;
}
BigInteger BigInteger::module()const
{
	BigInteger result(*this);
	result.sign = '+';
	return result;
}






BigInteger BigInteger::operator*(const __int8 other) const
{
	BigInteger result(*this);
	result *= other;
	return result;
}
BigInteger BigInteger::operator*(const unsigned __int8 other) const
{
	BigInteger result(*this);
	result *= other;
	return result;
}
BigInteger BigInteger::operator*(const __int16 other) const
{
	BigInteger result(*this);
	result *= other;
	return result;
}
BigInteger BigInteger::operator*(const unsigned __int16 other) const
{
	BigInteger result(*this);
	result *= other;
	return result;
}
BigInteger BigInteger::operator*(const __int32 other) const
{
	BigInteger result(*this);
	result *= other;
	return result;
}
BigInteger BigInteger::operator*(const unsigned __int32 other) const
{
	BigInteger result(*this);
	result *= (unsigned __int64)other;
	return result;
}
BigInteger BigInteger::operator*(const __int64 other) const
{
	BigInteger result(*this);
	result *= other;
	return result;
}
BigInteger BigInteger::operator*(const unsigned __int64 other) const
{
	BigInteger result(*this);
	result *= other;
	return result;
}


BigInteger BigInteger::operator+(const __int8 other) const
{
	BigInteger result(*this);
	result += other;
	return result;
}
BigInteger BigInteger::operator+(const unsigned __int8 other) const
{
	BigInteger result(*this);
	result += other;
	return result;
}
BigInteger BigInteger::operator+(const __int16 other) const
{
	BigInteger result(*this);
	result += other;
	return result;
}
BigInteger BigInteger::operator+(const unsigned __int16 other) const
{
	BigInteger result(*this);
	result += other;
	return result;
}
BigInteger BigInteger::operator+(const __int32 other) const
{
	BigInteger result(*this);
	result += other;
	return result;
}
BigInteger BigInteger::operator+(const unsigned __int32 other) const
{
	BigInteger result(*this);
	result += (unsigned __int64)other;
	return result;
}
BigInteger BigInteger::operator+(const __int64 other) const
{
	BigInteger result(*this);
	result += other;
	return result;
}
BigInteger BigInteger::operator+(const unsigned __int64 other) const
{
	BigInteger result(*this);
	result += other;
	return result;
}


BigInteger BigInteger::operator-(const __int8 other) const
{
	BigInteger result(*this);
	result -= other;
	return result;
}
BigInteger BigInteger::operator-(const unsigned __int8 other) const
{
	BigInteger result(*this);
	result -= other;
	return result;
}
BigInteger BigInteger::operator-(const __int16 other) const
{
	BigInteger result(*this);
	result -= other;
	return result;
}
BigInteger BigInteger::operator-(const unsigned __int16 other) const
{
	BigInteger result(*this);
	result -= other;
	return result;
}
BigInteger BigInteger::operator-(const __int32 other) const
{
	BigInteger result(*this);
	result -= other;
	return result;
}
BigInteger BigInteger::operator-(const unsigned __int32 other) const
{
	BigInteger result(*this);
	result -= (unsigned __int64)other;
	return result;
}
BigInteger BigInteger::operator-(const __int64 other) const
{
	BigInteger result(*this);
	result -= other;
	return result;
}
BigInteger BigInteger::operator-(const unsigned __int64 other) const
{
	BigInteger result(*this);
	result -= other;
	return result;
}
//BigInteger operator-(const __int8 other, const BigInteger num)
//{
//	return (BigInteger)other - num;
//}
//BigInteger operator-(const unsigned __int8 other, const BigInteger num)
//{
//	return (BigInteger)other - num;
//}
//BigInteger operator-(const __int16 other, const BigInteger num)
//{
//	return (BigInteger)other - num;
//}
//BigInteger operator-(const unsigned __int16 other, const BigInteger num)
//{
//	return (BigInteger)other - num;
//}
//BigInteger operator-(const __int32 other, const BigInteger num)
//{
//	return (BigInteger)other - num;
//}
//BigInteger operator-(const unsigned __int32 other, const BigInteger num)
//{
//	return (BigInteger)other - num;
//}
//BigInteger operator-(const __int64 other, const BigInteger num)
//{
//	return (BigInteger)other - num;
//}
//BigInteger operator-(const unsigned __int64 other, const BigInteger num)
//{
//	return (BigInteger)other - num;
//}
//BigInteger operator-(const char *other, const BigInteger num)
//{
//	return (BigInteger)other - num;
//}

BigInteger BigInteger::operator/(const __int8 other) const
{
	BigInteger result(*this);
	result /= other;
	return result;
}
BigInteger BigInteger::operator/(const unsigned __int8 other) const
{
	BigInteger result(*this);
	result /= other;
	return result;
}
BigInteger BigInteger::operator/(const __int16 other) const
{
	BigInteger result(*this);
	result /= other;
	return result;
}
BigInteger BigInteger::operator/(const unsigned __int16 other) const
{
	BigInteger result(*this);
	result /= other;
	return result;
}
BigInteger BigInteger::operator/(const __int32 other) const
{
	BigInteger result(*this);
	result /= other;
	return result;
}
BigInteger BigInteger::operator/(const unsigned __int32 other) const
{
	BigInteger result(*this);
	result /= (unsigned __int64)other;
	return result;
}
BigInteger BigInteger::operator/(const __int64 other) const
{
	BigInteger result(*this);
	result /= other;
	return result;
}
BigInteger BigInteger::operator/(const unsigned __int64 other) const
{
	BigInteger result(*this);
	result /= other;
	return result;
}



BigInteger BigInteger::operator%(const __int8 other) const
{
	BigInteger result(*this);
	result %= other;
	return result;
}
BigInteger BigInteger::operator%(const unsigned __int8 other) const
{
	BigInteger result(*this);
	result %= other;
	return result;
}
BigInteger BigInteger::operator%(const __int16 other) const
{
	BigInteger result(*this);
	result %= other;
	return result;
}
BigInteger BigInteger::operator%(const unsigned __int16 other) const
{
	BigInteger result(*this);
	result %= other;
	return result;
}
BigInteger BigInteger::operator%(const __int32 other) const
{
	BigInteger result(*this);
	result %= other;
	return result;
}
BigInteger BigInteger::operator%(const unsigned __int32 other) const
{
	BigInteger result(*this);
	result %= (unsigned __int64)other;
	return result;
}
BigInteger BigInteger::operator%(const __int64 other) const
{
	BigInteger result(*this);
	result %= other;
	return result;
}
BigInteger BigInteger::operator%(const unsigned __int64 other) const
{
	BigInteger result(*this);
	result %= other;
	return result;
}



bool BigInteger::operator==(const __int8 other)const{return *this == (BigInteger)(other);}
bool BigInteger::operator==(const __int16 other)const{return *this == (BigInteger)(other);}
bool BigInteger::operator==(const __int32 other)const{return *this == (BigInteger)(other);}
bool BigInteger::operator==(const __int64 other)const{return *this == (BigInteger)(other);}
bool BigInteger::operator==(const unsigned __int8 other)const{return *this == (BigInteger)(other);}
bool BigInteger::operator==(const unsigned __int16 other)const{return *this == (BigInteger)(other);}
bool BigInteger::operator==(const unsigned __int32 other)const{return *this == (BigInteger)((unsigned __int64)other);}
bool BigInteger::operator==(const unsigned __int64 other)const{return *this == (BigInteger)(other);}
bool BigInteger::operator==(const char *other)const{return *this == (BigInteger)(other);}

bool BigInteger::operator!=(const __int8 other)const{return *this != (BigInteger)(other);}
bool BigInteger::operator!=(const __int16 other)const{return *this != (BigInteger)(other);}
bool BigInteger::operator!=(const __int32 other)const{return *this != (BigInteger)(other);}
bool BigInteger::operator!=(const __int64 other)const{return *this != (BigInteger)(other);}
bool BigInteger::operator!=(const unsigned __int8 other)const{return *this != (BigInteger)(other);}
bool BigInteger::operator!=(const unsigned __int16 other)const{return *this != (BigInteger)(other);}
bool BigInteger::operator!=(const unsigned __int32 other)const{return *this != (BigInteger)((unsigned __int64)other);}
bool BigInteger::operator!=(const unsigned __int64 other)const{return *this != (BigInteger)(other);}
bool BigInteger::operator!=(const char *other)const{return *this != (BigInteger)(other);}


bool BigInteger::operator>=(const __int8 other)const{return *this >= (BigInteger)(other);}
bool BigInteger::operator>=(const __int16 other)const{return *this >= (BigInteger)(other);}
bool BigInteger::operator>=(const __int32 other)const{return *this >= (BigInteger)(other);}
bool BigInteger::operator>=(const __int64 other)const{return *this >= (BigInteger)(other);}
bool BigInteger::operator>=(const unsigned __int8 other)const{return *this >= (BigInteger)(other);}
bool BigInteger::operator>=(const unsigned __int16 other)const{return *this >= (BigInteger)(other);}
bool BigInteger::operator>=(const unsigned __int32 other)const{return *this >= (BigInteger)((unsigned __int64)other);}
bool BigInteger::operator>=(const unsigned __int64 other)const{return *this >= (BigInteger)(other);}
bool BigInteger::operator>=(const char *other)const{return *this >= (BigInteger)(other);}


bool BigInteger::operator>(const __int8 other)const{return *this > (BigInteger)(other);}
bool BigInteger::operator>(const __int16 other)const{return *this > (BigInteger)(other);}
bool BigInteger::operator>(const __int32 other)const{return *this > (BigInteger)(other);}
bool BigInteger::operator>(const __int64 other)const{return *this > (BigInteger)(other);}
bool BigInteger::operator>(const unsigned __int8 other)const{return *this > (BigInteger)(other);}
bool BigInteger::operator>(const unsigned __int16 other)const{return *this > (BigInteger)(other);}
bool BigInteger::operator>(const unsigned __int32 other)const{return *this > (BigInteger)((unsigned __int64)other);}
bool BigInteger::operator>(const unsigned __int64 other)const{return *this > (BigInteger)(other);}
bool BigInteger::operator>(const char *other)const{return *this > (BigInteger)(other);}




bool BigInteger::operator<=(const __int8 other)const{return *this <= (BigInteger)(other);}
bool BigInteger::operator<=(const __int16 other)const{return *this <= (BigInteger)(other);}
bool BigInteger::operator<=(const __int32 other)const{return *this <= (BigInteger)(other);}
bool BigInteger::operator<=(const __int64 other)const{return *this <= (BigInteger)(other);}
bool BigInteger::operator<=(const unsigned __int8 other)const{return *this <= (BigInteger)(other);}
bool BigInteger::operator<=(const unsigned __int16 other)const{return *this <= (BigInteger)(other);}
bool BigInteger::operator<=(const unsigned __int32 other)const{return *this <= (BigInteger)((unsigned __int64)other);}
bool BigInteger::operator<=(const unsigned __int64 other)const{return *this <= (BigInteger)(other);}
bool BigInteger::operator<=(const char *other)const{return *this <= (BigInteger)(other);}


bool BigInteger::operator<(const __int8 other)const{return *this < (BigInteger)(other);}
bool BigInteger::operator<(const __int16 other)const{return *this < (BigInteger)(other);}
bool BigInteger::operator<(const __int32 other)const{return *this < (BigInteger)(other);}
bool BigInteger::operator<(const __int64 other)const{return *this < (BigInteger)(other);}
bool BigInteger::operator<(const unsigned __int8 other)const{return *this < (BigInteger)(other);}
bool BigInteger::operator<(const unsigned __int16 other)const{return *this < (BigInteger)(other);}
bool BigInteger::operator<(const unsigned __int32 other)const{return *this < (BigInteger)((unsigned __int64)other);}
bool BigInteger::operator<(const unsigned __int64 other)const{return *this < (BigInteger)(other);}
bool BigInteger::operator<(const char *other)const{return *this < (BigInteger)(other);}




BigInteger BigInteger::fact(size_t value)
{
	BigInteger result(1);
	for(size_t i = 1; i <= value; ++i)
		result *= i;

	return result;
}

BigInteger BigInteger::div10()
{
	if(data.size() == 1)
	{
		data[0] = 0;
		sign = '+';
		return *this;
	}
	for(vector<__int8>::size_type i = 0; i < data.size() - 1; ++i)
		data[i] = data[i + 1];
	data.pop_back();
	return *this;
}