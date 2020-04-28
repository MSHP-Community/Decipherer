#include "Hamming.h"

#include <iostream>
#include <cstring>
#include <string>
#include <vector>


// The code for the Hamming class:

Hamming::Hamming() // create object with value = 0
{
	Binary t1, t2;
	this->fullSection = t1;
	this->firstClean = t2;
	this->finalCleanInt = 0;
	this->finalCleanString = "00000000000";
}

Hamming::Hamming(char* s) // create object from value = char[16] and cleaars it
{
	Binary t(s);
	Binary t1;
	this->fullSection = t;
	this->firstClean = t1;
	this->finalCleanInt = 0;
	this->finalCleanString = "00000000000";
	clean(); // clears the text
}

void Hamming::clean() // the main method that calculates the error using the check() method is fixed and defines the package without protection
{
	int change;
	change = check(); // find error using first_check(), second_check(), third_check(), fourth_check() and records error number in Base-2 inc change
	this->firstClean = this->fullSection;

	Binary tmp = this->fullSection; /* */
	if (tmp.at(change - 1)) // the restoration of the damaged package
		this->firstClean.at(change - 1) = false;
	else
		this->firstClean.at(change - 1) = true;

	this->fullSection = tmp; /* */
	delete_excess(firstClean); // deletes defender bits
}

int Hamming::clean_in_int() // return clean recovery packet in int
{
	return finalCleanInt;
}

std::string Hamming::clean_in_string() // return clean recovery packet in string
{
	return finalCleanString;
}

int Hamming::check() // method that find error using first_check(), second_check(), third_check(), fourth_check(), return error number in Base-2
{
	char s[5] = {};
	if (first_check()) // checking for the first defender bit
		s[3] = '1';
	else
		s[3] = '0';
	if (second_check()) // checking for the second defender bit
		s[2] = '1';
	else
		s[2] = '0';
	if (third_check()) // checking for the third defender bit
		s[1] = '1';
	else
		s[1] = '0';
	if (fourth_check()) // checking for the fourth defender bit
		s[0] = '1';
	else
		s[0] = '0';

	return to_int(s); // returns the position where the loss occurred
}

int Hamming::first_check() // checking for the first defender bit, return 1 or 0
{
	int count = 0;
	for (int i = 0; i < 15; i += 2)
	{
		if (this->fullSection.at(i))
			count++;
	}
	return (count % 2 == 0 ? 0 : 1);
}

int Hamming::second_check() // checking for the second defender bit, return 1 or 0
{
	int count = 0;
	for (int i = 0; i < 15; ++i)
	{
		if (i % 4 == 1)
		{
			if (this->fullSection.at(i))
				count++;
			if (this->fullSection.at(i + 1))
				count++;
		}
	}
	return (count % 2 == 0 ? 0 : 1);
}

int Hamming::third_check() // checking for the third defender bit, return 1 or 0
{
	int count = 0;
	for (int i = 0; i < 15; ++i)
	{
		if (i % 8 == 3)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (this->fullSection.at(i + j))
					count++;
			}
		}
	}
	return (count % 2 == 0 ? 0 : 1);
}

int Hamming::fourth_check() // checking for the third defender bit, return 1 or 0
{
	int count = 0;
	for (int i = 7; i < 15; ++i)
	{
		if (this->fullSection.at(i))
			count++;
	}
	return (count % 2 == 0 ? 0 : 1);
}

template <typename T>
int Hamming::to_int(T* s) const  // convert from Base-2 to Base-10 for char with 4 symbols (use for recovery of losses)
{
	std::string str(s);
	int count = 0, n = 1;

	for (int i = str.size() - 1; i >= 0; --i)
	{
		if (str[i] == '1')
			count += n;
		n *= 2;
	}

	return count;
}

long long Hamming::to_bin(long long value) const  // convert from Base-10 to Base-2 (not used)
{
	long long int bin = 0, k = 1;

	while (value)
	{
		bin += (value % 2) * k;
		k *= 10;
		value /= 2;
	}

	return value;
}


void Hamming::delete_excess(Binary section) // method that delete protecting bits
{
	std::vector <bool> b(15, false);
	std::vector <bool>::iterator it;

	int i = 0;

	for (it = b.begin(); it < b.end(); ++it, ++i) // copy value from packet to vector
	{
		if (section.at(i))
			*it = true;
		else
			*it = false;
	}
	b.erase(b.begin() + 7); // deletes defender bit on position 8
	b.erase(b.begin() + 3); // deletes defender bit on position 4
	b.erase(b.begin() + 1); // deletes defender bit on position 2
	b.erase(b.begin()); // deletes defender bit on position 1

	char s[12] = {};
	for (i = 0, it = b.begin(); it < b.end(); ++it, ++i) // copy value from vector to char[11]
	{
		if (*it)
			s[i] = '1';
		else
			s[i] = '0';
	}
	std::string str(s);
	this->finalCleanString = str; // copy value to attribute as string
	this->finalCleanInt = to_int(s); // copy value to attribute as int
}

std::istream& operator>>(std::istream& in, Hamming& tmp) // enters value
{
	char s[16] = {};
	in >> s;
	Hamming t(s);
	tmp = t;
	return in;
}

std::ostream& operator<<(std::ostream& out, Hamming& tmp) // outputs a primordial package
{
	tmp.fullSection.write();
	return out;
}

// The code for the Hamming class is over


/*----------------------------------------*/


// The code for the Binary class:

Hamming::Binary::Binary() // create object with value = 0
{
	for (int i = 0; i < 15; ++i)
	{
		this->data[i] = false;
	}
}

Hamming::Binary::Binary(int value) // create object from value = int
{
	int bin = this->to_bin(value);
	int i = 0;

	for (int i = 0; i < 15; ++i)
	{
		this->data[i] = false;
	}

	while (value) {
		if (value % 2)
			this->data[14 - i] = true;
		value /= 2;
		++i;
	}
}

Hamming::Binary::Binary(char* s) // create object from value = char[16]
{
	for (int i = 0; i < 15; ++i)
	{
		this->data[i] = false;
	}
	int num = 0;
	for (int i = 15 - strlen(s); i < 15; ++i)
	{
		if (s[num] == '1')
			this->data[i] = true;
		++num;
	}
}

int Hamming::Binary::to_bin(int value) const // convert from Base-10 to Base-2
{
	int bin = 0, k = 1;

	while (value)
	{
		bin += (value % 2) * k;
		k *= 10;
		value /= 2;
	}

	return value;
}

int Hamming::Binary::to_int() const // convert from Base-2 to Base-10
{
	int count = 0, n = 1;

	for (int i = 14; i >= 0; --i)
	{
		if (this->data[i])
			count += n;
		n *= 2;
	}

	return count;
}

Hamming::Binary& Hamming::Binary::operator+(Binary& tmp) // the addition of two of the packages as mathematical objects (not used)
{
	int res;
	res = this->to_int() + tmp.to_int();
	Binary r(res);
	for (int i = 0; i < 15; ++i)
		tmp.data[i] = r.data[i];
	return tmp;
}

Hamming::Binary& Hamming::Binary::operator-(Binary& tmp) // subtraction of two of the packages as mathematical objects (not used)
{
	int res;
	res = this->to_int() - tmp.to_int();
	Binary r(res);
	for (int i = 0; i < 15; ++i)
		tmp.data[i] = r.data[i];
	return tmp;
}

Hamming::Binary& Hamming::Binary::operator*(Binary& tmp) // multiplication of two of the packages as mathematical objects (not used)
{
	int res;
	res = this->to_int() * tmp.to_int();
	Binary r(res);
	for (int i = 0; i < 15; ++i)
		tmp.data[i] = r.data[i];
	return tmp;
}

Hamming::Binary& Hamming::Binary::operator/(Binary& tmp) // division of two of the packages as mathematical objects (not used)
{
	int res;
	res = this->to_int() / tmp.to_int();
	Binary r(res);
	for (int i = 0; i < 15; ++i)
		tmp.data[i] = r.data[i];
	return tmp;
}

Hamming::Binary& Hamming::Binary::operator=(Binary& tmp) // assignment overload
{
	for (int i = 0; i < 15; ++i)
	{
		this->at(i) = tmp.at(i);
	}
	return *(this);
}

bool& Hamming::Binary::at(int index) // provide access
{
	return this->data[index];
}

void Hamming::Binary::read() // enters value
{
	char s[16] = {};
	std::cin >> s;
	Binary b(s);
	*(this) = b;
}

#if true // if true the output value will be with non-significant zeros, if false the outputs value will be without non-significant zeros

void Hamming::Binary::write() const // outputs value with non-significant zeros
{
	for (int i = 0; i < 15; ++i)
	{
		if (this->data[i])
			std::cout << 1;
		else
			std::cout << 0;
	}
}

#else

void Hamming::Binary::write() const // outputs value without non-significant zeros
{
	int num = 0;
	bool flag = false;
	for (int i = 0; i < 15 && !flag; ++i)
	{
		if (this->data[i])
			flag = true;
		num = i;
	}
	for (int i = num; i < 15; ++i)
	{
		if (this->data[i])
			std::cout << 1;
		else
			std::cout << 0;
	}
}

#endif // true

// The code for the Binary class is over