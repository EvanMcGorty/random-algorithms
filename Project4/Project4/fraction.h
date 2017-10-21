#pragma once
#include <sstream>
#include <iostream>
#include <string>



template<typename pty, bool autosimplify = true, pty infnanret = 0>
class fraction
{
public:
	fraction()
	{
		num = 0;
		den = 1;
	}

	template<typename init>
	fraction(init a)
	{
		num = a;
		den = 1;
	}

	template<typename numinit,typename deninit>
	fraction(numinit a, deninit b)
	{
		if (autosimplify)
		{
			pty c = gcd(a, b);
			num = a / c;
			den = b / c;
		}
		else
		{
			num = a;
			den = b;
		}
	}

	fraction(fraction<pty, !autosimplify> a)
	{
		if (autosimplify)
		{
			pty c = gcd(a.num, a.den);
			num = a.num / c;
			den = a.den / c;
		}
		else
		{
			num = a.num;
			den = a.den;
		}
	}

	fraction(float a) //some numbers will cause an infinite loop
	{
		pty ret{ 1 };
		while ((a)!=int(a)) //if a is a whole memory
		{
			a = a * 2;
			ret = ret * 2;
		}
		fraction{ int(a),ret };
		num = int(a);
		den = ret;
	}

	
	fraction(double a) //works even less than float initialization
	{
		pty ret{ 1 };
		while ((a) != int(a)) //if a is a whole memory
		{
			a = a * 2;
			ret = ret * 2;
		}
		num = int(a);
		den = ret;
	}
	

	fraction(std::string a)
	{
		strin(a);
	}

	operator pty()
	{
		if (den == 0)
		{
			return infnanret;
		}
		else
		{
			return num / den;
		}
	}

	operator float()
	{
		return num / den;
	}

	operator double()
	{
		return num / den;
	}

	void operator=(pty a)
	{
		num = a;
		den = 1;
	}

	template<typename t, bool a, t inr>
	friend std::ostream& operator<<(std::ostream& dest, const fraction<t, a, inr>& val);

	template<typename t, bool a, t inr>
	friend std::istream& operator>>(std::istream& val, fraction<t, a, inr>& dest);


	template<bool t,typename lt,lt inr>
	void assign(fraction<lt, t> a)
	{
		num = a.num;
		den = a.den;
	}

	fraction<pty> operator+(pty a)
	{
		return{ num + (a*den),den };
	}

	fraction<pty> operator+(float a)
	{
		return{ num + (a*den),den };
	}

	fraction<pty> operator+(double a)
	{
		return{ num + (a*den),den };
	}


	fraction<pty> operator-(pty a)
	{
		return{ num - (a*den),den };
	}

	fraction<pty> operator-(float a)
	{
		return{ num - (a*den),den };
	}

	fraction<pty> operator-(double a)
	{
		return{ num - (a*den),den };
	}


	fraction<pty> operator*(pty a)
	{
		return{ num * a,den };
	}

	fraction<pty> operator*(float a)
	{
		return{ num * a,den };
	}

	fraction<pty> operator*(double a)
	{
		return{ num * a,den };
	}


	fraction<pty> operator/(pty a)
	{
		return{ num ,den*a };
	}

	fraction<pty> operator/(float a)
	{
		return{ num ,den*a };
	}

	fraction<pty> operator/(double a)
	{
		return{ num ,den*a };
	}


	fraction<pty> operator%(pty a)
	{
		if (a == 0 || den == 0) { return{ 1,0 }; }
		return{ num % (a*den),den };
	}

	fraction<pty> operator%(float a)
	{
		if (a == 0 || den == 0) { return{ 1,0 }; }
		return{ num % (a*den),den };
	}

	fraction<pty> operator%(double a)
	{
		if (a == 0 || den == 0) { return{ 1,0 }; }
		return{ num % (a*den),den };
	}



	fraction<pty> operator+(fraction<pty, autosimplify, infnanret> a) {
		pty newnum;
		pty newden;
		newnum = (num * a.den) + (a.num * den);
		newden = den * a.den;
		return fraction{ newnum,newden };
	}

	fraction<pty> operator-(fraction<pty, autosimplify, infnanret> a) {
		pty newnum;
		pty newden;
		newnum = (num * a.den) - (a.num * den);
		newden = den * a.den;
		return fraction{ newnum,newden };
	}

	fraction<pty> operator*(fraction<pty, autosimplify, infnanret> a) {
		pty newnum;
		pty newden;
		newnum = num *(a.num);
		newden = den *(a.den);
		return fraction{ newnum,newden };
	}

	fraction<pty> operator/(fraction<pty, autosimplify, infnanret> a) {
		pty newnum;
		pty newden;
		newnum = num*(a.den);
		newden = den*(a.num);
		return{ newnum,newden };
	}

	fraction<pty> operator%(fraction<pty, autosimplify, infnanret> a) {
		pty newnum;
		pty newden;
		if (den && a.num)
		{
			newnum = (num * a.den) % (a.num * den);
			newden = den * a.den;
			if (!newnum && !newden)
			{
				newnum = 1;
				newden = 0;
			}
			return fraction{ newnum,newden };
		}
		else
		{
			return fraction{ 1,0 };
		}
	}

	fraction<pty> operator^(fraction<pty, autosimplify, infnanret> a) {
		if (!den) //if self is infinite
		{
			if (!a.num) //if a is equal to 0
			{
				return fraction{ 1,1 };
			}
			else if (a.num < 0)
			{
				return fraction{ 0,1 };
			}
			else //if a is more than 0
			{
				return fraction{ 0,1 };
			}
		}
		if (!a.den) //if a is infinite
		{
			if (!num) //if self is equal to 0
			{
				return fraction{ 0,1 };
			}
			else if (num == 1 || num == -1)
			{
				return fraction{ 1,1 };
			}
			else //if self is not equal to 0
			{
				return fraction{ 1,0 };
			}
		}
		return operator^(a.floored());
	}


	template<bool t,typename lt,lt inr>
	fraction<pty> add(fraction<lt, t> a) {
		pty newnum;
		pty newden;
		newnum = (num * a.den) + (a.num * den);
		newden = den * a.den;
		return fraction{ newnum,newden };
	}

	template<bool t,typename lt,lt inr>
	fraction<pty> sub(fraction<lt, t> a) {
		pty newnum;
		pty newden;
		newnum = (num * a.den) - (a.num * den);
		newden = den * a.den;
		return fraction{ newnum,newden };
	}

	template<bool t,typename lt,lt inr>
	fraction<pty> mul(fraction<lt, t> a) {
		pty newnum;
		pty newden;
		newnum = num *(a.num);
		newden = den *(a.den);
		return fraction{ newnum,newden };
	}

	template<bool t,typename lt,lt inr>
	fraction<pty> div(fraction<lt, t> a) {
		pty newnum;
		pty newden;
		newnum = num*(a.den);
		newden = den*(a.num);
		return{ newnum,newden };
	}

	template<bool t,typename lt,lt inr>
	fraction<pty> mod(fraction<lt, t> a) {
		pty newnum;
		pty newden;
		if (den && a.num)
		{
			newnum = (num * a.den) % (a.num * den);
			newden = den * a.den;
			if (!newnum && !newden)
			{
				newnum = 1;
				newden = 0;
			}
			return fraction{ newnum,newden };
		}
		else
		{
			return fraction{ 1,0 };
		}
	}

	template<bool t,typename lt,lt inr>
	fraction<pty> pow(fraction<lt, t> a) {
		if (!den) //if self is infinite
		{
			if (!a.num) //if a is equal to 0
			{
				return fraction{ 1,1 };
			}
			else if (a.num < 0)
			{
				return fraction{ 0,1 };
			}
			else //if a is more than 0
			{
				return fraction{ 0,1 };
			}
		}
		if (!a.den) //if a is infinite
		{
			if (!num) //if self is equal to 0
			{
				return fraction{ 0,1 };
			}
			else if (num == 1 || num == -1)
			{
				return fraction{ 1,1 };
			}
			else //if self is not equal to 0
			{
				return fraction{ 1,0 };
			}
		}
		return operator^(a.floored());
	}


	fraction<pty> operator^(pty a)
	{
		pty newnum{ num };
		pty newden{ den };
		while (a >= 1)
		{
			newnum = newnum*num;
			newden = newden*den;
			--a;
		}
		return fraction{ newnum,newden };
	}



	template<bool t,typename lt,lt inr>
	bool notequal(fraction<lt, t> a)
	{
		if (num != a.num)
		{
			if (den != a.den)
			{
				return true;
			}
		}
		return false;
	}

	template<bool t,typename lt,lt inr>
	bool equal(fraction<lt, t> a) {
		if (num == a.num)
		{
			if (den == a.den)
			{
				return true;
			}
		}
		return false;
	}

	template<bool t,typename lt,lt inr>
	bool more(fraction<lt, t> a) {
		return (num * a.den) > (a.num * den);
	}

	template<bool t,typename lt,lt inr>
	bool moreequal(fraction<lt, t> a) {
		return (num * a.den) >= (a.num * den);
	}

	template<bool t,typename lt,lt inr>
	bool less(fraction<lt, t> a) {
		return (num * a.den) < (a.num * den);
	}

	template<bool t,typename lt,lt inr>
	bool lessequal(fraction<lt, t> a) {
		return (num * a.den) <= (a.num * den);
	}

	
	bool operator!=(fraction<pty, autosimplify,infnanret> a)
	{
		if (num != a.num)
		{
			if (den != a.den)
			{
				return true;
			}
		}
		return false;
	}

	bool operator==(fraction<pty, autosimplify, infnanret> a) {
		if (num == a.num)
		{
			if (den == a.den)
			{
				return true;
			}
		}
		return false;
	}

	bool operator>(fraction<pty, autosimplify, infnanret> a) {
		return (num * a.den) > (a.num * den);
	}

	bool operator>=(fraction<pty, autosimplify, infnanret> a) {
		return (num * a.den) >= (a.num * den);
	}

	bool operator<(fraction<pty, autosimplify, infnanret> a) {
		return (num * a.den) < (a.num * den);
	}

	bool operator<=(fraction<pty, autosimplify, infnanret> a) {
		return (num * a.den) <= (a.num * den);
	}

	void operator++()
	{
		num = num + den;
	}

	void operator--()
	{
		num = num - den;
	}

	std::string strout()
	{
		std::stringstream ret;
		ret << num << "/" << den;
		return ret.str();
	}

	void strin(std::string a)
	{
		int index = 0;
		int input = 0;
		bool sign = false; //false means positive(no sign)
		pty numerator = 0;
		pty denomenator = 1; //set to one in case of a not being a fraction

		if (a[0] == '-') //checking if a is negative
		{
			sign = true;
			a.erase(0, 1);
		}


		int cur; //used to put characters to

		bool divordec = false; //true means '/', false means '.'


		for (int& i = index; i != a.length(); ++i) //used for the first half of number, eg numerator of a fraction or pre decimal point number
		{

			if ((a[i] > '9') || (a[i]<'0')) //if elem is not a number character
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
				operator=(numerator);
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
				if ((a[i] > '9') || (a[i] < '0')) //if elem is not a number character
				{
					if (sign) { numerator *= (-1); }
					operator=({ numerator,denomenator });
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
				if ((a[i] > '9') || (a[i] < '0'))
				{
					if (sign) { numerator *= (-1); }
					operator=({ numerator,denomenator });
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
		operator=({ numerator,denomenator });
	}

	pty num;
	pty den;

	void simp()
	{
		pty c = gcd(num, den);
		num = num / c;
		den = den / c;
	}


private:

	pty gcd(pty a, pty b)
	{
		if (b == 0) {
			return a;
		}
		else
		{
			return gcd(b, a % b);
		}
	}

};

template<typename t, bool a, t inr>
std::ostream& operator<<(std::ostream& dest, const fraction<t, a, inr>& val)
{
	dest << val.num << '/' << val.den;
	return dest;
}



template<typename t, bool a, t inr>
std::istream& operator>>(std::istream& val, fraction<t, a, inr>& dest)
{
	std::string dir;
	val >> dir;
	dest.strin(dir);
	return val;
}



using rat = fraction<int, true>;
using mrat = fraction<int, false>;

