#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

template<typename pty, int def = 0 >
class matrix
{
public:
	matrix(int x, int y)
	{
		std::vector<pty> rows;
		for (int i = x; i != 0; --i)
		{
			rows.push_back(pty{ def });
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

	std::vector<pty>& row(int x)
	{
		return mat[x];
	}

	std::string str()
	{
		std::stringstream ret;
		for (int i = 0; i != height(); ++i)
		{
			for (int si = 0; si != length(); ++si)
			{
				ret << mat[i][si] << "	";
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

template<typename elty,int eldef>
std::ostream& operator<<(std::ostream& target, matrix<elty,eldef> object)
{
	for (int i = 0; i != object.height(); ++i)
	{
		for (int si = 0; si != object.length(); ++si)
		{
			target << object.elem(i,si) << "	";
		}
		target << std::endl << std::endl << std::endl;
	}
	return target;
}