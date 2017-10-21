#include "fraction.h"
#include "matrix.h"
#include "definitions.h"
#include "input.h"
#include "matrixmath.h"
#include <iostream>
#include <cmath>
#define prompt {char a; std::cin >> a;}


void runmatrixsolver()
{
	auto a = matrixinput<long long>();

	std::cout << std::endl;

	a = rowreduce(a);

	std::cout << a.str();

	auto r = rowsubs(a);

	for (int i = 1; i != r.size(); ++i) { std::cout << r[i] << std::endl; }
}

void negbasetwo(int szof)
{
	std::vector<bool> binval(szof);
	for (int i = 0; i != pow(2, szof); ++i)
	{
		int caryover = true;
		for (int it = 0; it != binval.size(); ++it)
		{
			if (caryover&&binval[it])
			{
				caryover = true;
				binval[it] = false;
			}
			else if (caryover || binval[it])
			{
				caryover = false;
				binval[it] = true;
			}
		}


		int retval = 0;
		{
			int inc = 0;
			int curexp = 1;

			while (inc != binval.size())
			{
				//std::cout<<inc<<std::endl<<curexp<<std::endl<<retval<<std::endl<<std::endl;
				if (binval[inc])
				{
					retval += curexp;
				}

				++inc;
				curexp *= (-2);
			}
		}
		std::cout << "the number\t\t\t\t" << i + 1 << std::endl;
		std::cout << "translated to normal binary\t\t";
		for (int i = 0; i != binval.size(); ++i)
		{
			if (binval[i])
			{
				std::cout << 1;
			}
			else
			{
				std::cout << 0;
			}
		}
		std::cout << std::endl << "reinterpreted in base negative 2\t" << retval << std::endl << std::endl;
	}
}


int main()
{
	return 0;
}