#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<sstream>

enum class dir
{
	up = 0, down = 1, left = 2, right = 3

};


void nextdir(dir& a)
{
	switch (a)
	{

	}
}

struct coord
{
	coord(int a, int b)
	{
		x = a;
		y = b;
	}

	bool operator==(coord a)
	{
		return(x == a.x && y == a.y);
	}
	bool operator!=(coord a)
	{
		return(x != a.x || y != a.y);
	}

	coord operator+(coord a)
	{
		return{ x + a.x,y + a.y };
	}

	coord move(dir b, int a = 1)
	{
		coord ret(x, y);
		switch (b)
		{
		case dir::up:
			for (int i = 0; i != a; ++i)
			{
				--ret.x;
				//++ret.y;
			}
			break;
		case dir::down:
			for (int i = 0; i != a; ++i)
			{
				++ret.x;
				//--ret.y;
			}
			break;
		case dir::left:
			for (int i = 0; i != a; ++i)
			{
				--ret.y;
				//--ret.x;
			}
			break;
		case dir::right:
			for (int i = 0; i != a; ++i)
			{
				++ret.y;
				//++ret.x;
			}
			break;
		}
		return ret;
	}

	int x;
	int y;
};


template<typename pty>
class matrix
{
public:
	matrix(int x, int y)
	{
		std::vector<pty> rows;
		for (int i = x; i != 0; --i)
		{
			rows.push_back(pty{});
		}
		for (int i = y; i != 0; --i)
		{
			mat.push_back(rows);
		}
	}

	pty& elem(int x, int y)
	{
		return mat[y][x];
	}

	pty& elem(coord a)
	{
		return mat[a.y][a.x];
	}

	pty& operator[](coord a)
	{
		return mat[a.y][a.x];
	}

	std::vector<pty>& row(int x)
	{
		return mat[x];
	}

	template<int mintillen = 0>
	std::string tiledstr()
	{
		
			std::stringstream ret;

			int longestlen = mintillen;

			for (int i = 0; i != length(); ++i)
			{
				for (int i2 = 0; i2 != height(); ++i2)
				{
					std::stringstream s;
					s << elem(i, i2);
					int v = s.str().length();
					if (v > longestlen)
					{
						longestlen = v;
					}
				}
			}

			std::stringstream liness;

			for (int i = 0; i != longestlen; ++i)
			{
				liness << char(196);
			}
			std::string line = liness.str();


			ret << char(218);
			for (int i = 0; i != length() - 1; ++i)
			{
				ret << line << char(194);
			}
			ret << line << char(191) << '\n';

			for (int i = 0; i != height() - 1; ++i)
			{
				ret << char(179);
				for (int i2 = 0; i2 != length() - 1; ++i2)
				{
					std::string curst;
					std::stringstream curss;
					curss << elem(i2, i);
					curst = curss.str();
					for (int x = curst.length(); x != longestlen; ++x)
					{
						curst.push_back(' ');
					}
					ret << curst << char(179);
				}
				std::string curst;
				std::stringstream curss;
				curss << elem(length() - 1, i);
				curst = curss.str();
				for (int x = curst.length(); x != longestlen; ++x)
				{
					curst.push_back(' ');
				}
				ret << curst << char(179) << '\n';
				ret << char(195);
				for (int i2 = 0; i2 != length() - 1; ++i2)
				{
					ret << line << char(197);
				}
				ret << line << char(180) << '\n';
			}
			ret << char(179);
			for (int i2 = 0; i2 != length() - 1; ++i2)
			{
				std::string curst;
				std::stringstream curss;
				curss << elem(i2, height() - 1);
				curst = curss.str();
				for (int x = curst.length(); x != longestlen; ++x)
				{
					curst.push_back(' ');
				}
				ret << curst << char(179);
			}
			std::string curst;
			std::stringstream curss;
			curss << elem(length() - 1, height() - 1);
			curst = curss.str();
			for (int x = curst.length(); x != longestlen; ++x)
			{
				curst.push_back(' ');
			}
			ret << curst << char(179) << '\n';
			ret << char(192);
			for (int i = 0; i != length() - 1; ++i)
			{
				ret << line << char(193);
			}
			ret << line << char(217) << '\n';

			return ret.str();

	}

	std::string str()
	{
		std::stringstream ret;
		for (int i = 0; i != height(); ++i)
		{
			for (int si = 0; si != length(); ++si)
			{
				ret << mat[i][si] << "\t";
			}
			ret << std::endl << std::endl << std::endl;
		}
		return ret.str();
	}

	void print() { std::cout << str(); }
	void rowout(int a)
	{
		for (int i = 0; i != length(); ++i)
		{
			std::cout << row(a)[i];
		}
	}

	size_t height()
	{
		return mat.size();
	}
	size_t length()
	{
		return mat[0].size();
	}

private:
	std::vector<std::vector<pty>> mat;
};

template<typename elty>
std::ostream& operator<<(std::ostream& target, matrix<elty> object)
{
	for (int i = 0; i != object.height(); ++i)
	{
		for (int si = 0; si != object.length(); ++si)
		{
			target << object.elem(i, si) << "	";
		}
		target << std::endl << std::endl << std::endl;
	}
	return target;
}

/*
matrix<std::string> somematrix(5, 3);
somematrix.row(0) = { "these are","example","words","","3.14159265359" };
somematrix.row(1) = { "this","took","3","","whole" };
somematrix.row(2) = { "hours","to","make","","!!!!!" };
std::cout << somematrix.tiledstr();

┌─────────────┬─────────────┬─────────────┬─────────────┬─────────────┐
│these are    │example      │words        │             │3.14159265359│
├─────────────┼─────────────┼─────────────┼─────────────┼─────────────┤
│this         │took         │3            │             │whole        │
├─────────────┼─────────────┼─────────────┼─────────────┼─────────────┤
│hours        │to           │make         │             │!!!!!        │
└─────────────┴─────────────┴─────────────┴─────────────┴─────────────┘
it doesn't have holes in the command line
as a side note, the amount of room that it makes for each box is the length of the longest element.
*/
