#pragma once
#include "fraction.h"
#include "matrix.h"
#include "definitions.h"

template<typename frty>
fraction<frty> stringinput(std::string a, int& index)
{
	while (a[index] == ',')
	{
		++index;
	}
	bool sign = false; //false means positive(no sign)
	frty numerator = 0;
	frty denomenator = 1; //set to one in case of a not being a fraction

	if (a[index] == '-') //checking if a is negative
	{
		sign = true;
		++index;
	}


	int cur; //used to put characters to

	bool divordec = false; //true means '/', false means '.'


	for (int& i = index; i != a.length(); ++i) //used for the first half of number, eg numerator of a fraction or pre decimal point number
	{

		if ((a[i] > ascii9) || (a[i]<ascii0)) //if elem is not a number character
		{
			if (a[i] == '.') //if elem is our decimal point
			{
				divordec = false;
				goto exit1; //break from for loop
			}
			else if (a[i] == '/') //if elem is our "/" for a fraction
			{
				divordec = true;
				goto exit1; //break from for loop
			}
			if (sign) { numerator *= (-1); }
			return numerator;
		}

		numerator = numerator * 10;
		std::stringstream sts;
		sts << a[i];
		sts >> cur;
		numerator = numerator + cur;

	}
exit1: //used to break from previous for loop
	++index;

	if (divordec) //if fraction
	{
		denomenator = 0;
		for (int& i = index; i != a.length(); ++i)
		{
			if ((a[i] > ascii9) || (a[i] < ascii0)) //if elem is not a number character
			{
				if (sign) { numerator *= (-1); }
				return{ numerator,denomenator };
			}
			denomenator = denomenator * 10;
			std::stringstream sts;
			sts << a[i];
			sts >> cur;
			denomenator = denomenator + cur;
		}
	}
	else if (!divordec) //case of a decimal
	{
		for (int& i = index; i != a.length(); ++i)
		{
			if ((a[i] > ascii9) || (a[i] < ascii0))
			{
				if (sign) { numerator *= (-1); }
				return{ numerator,denomenator };
			}
			denomenator = denomenator * 10;
			numerator = numerator * 10;
			std::stringstream sts;
			sts << a[i];
			sts >> cur;
			numerator = numerator + cur;
		}
	}

	if (sign) { numerator *= (-1); }
	return{ numerator,denomenator };
}

template<typename elemty, int elemdef = 0 >
matrix<fraction<elemty>, elemdef> matrixinput()
{
	int matlen;
	int matwid;
	std::cout << "length of matrix(elements per row): ";
	std::cin >> matlen;
	std::cout << "width of matrix(amount of rows): ";
	std::cin >> matwid;

	matrix<fraction<elemty>, elemdef> ret(matlen, matwid);

	std::string a;

	std::vector<fraction<elemty>> cur;
	for (int i = 0; i != ret.height(); ++i)
	{
		std::cin >> a;
		a.push_back(' ');
		int ind = 0;
		for (int& index = ind; index < a.length(); ++index)
		{
			cur.push_back(stringinput<elemty>(a, index));
		}
		ret.row(i) = cur;
		cur.clear();
	}
	return ret;
}
