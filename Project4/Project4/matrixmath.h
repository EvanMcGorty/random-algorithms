#pragma once
#include "matrix.h"
#include "fraction.h"

template<typename pty>
matrix < fraction<pty> > rowreduce(matrix < fraction<pty> > current)
{


	if (current.height() != (current.length() - 1)) //ensuring height and length are solvable
	{
		return current;
	}


	for (int cycle = 0; cycle != current.height(); ++cycle) //reducing row sizes of each row
	{
		fraction<pty> vartosubst = current.row(cycle)[current.length() - (cycle + 1)];
		for (int r = current.height() - 1; r != cycle; --r) //multiplying each rows elements by the last simplified rows last element 
		{
			fraction<pty> tosubtr = (current.row(r)[current.height()-cycle]) / ((vartosubst)); //to subtract
			for (int i = 0; i != (current.length() - cycle); ++i)
			{
				current.row(r)[i] = current.row(r)[i] - (current.row(cycle)[i] * tosubtr);
			}

		}
	}



	return current;

}

//
template<typename pty>
std::vector<fraction<pty>> rowsubs(matrix<fraction<pty>> current)
{
	std::vector<fraction<pty>> ret; // return

	ret.push_back(pty{ 1 });//the value of one(each rows constant)
	int curelem = 1;
	for (int currentrow = current.height()-1; currentrow >= 0; --currentrow)//solve each row starting from last
	{
		
		fraction<pty> sumofthisrow = pty{ 0 };

		for (int i = 0; i != ret.size(); ++i)
		{
			sumofthisrow = sumofthisrow + (current.row(currentrow)[i] * ret[i]);
		}

		ret.push_back(fraction<pty>{pty{ -1 }} *(sumofthisrow / current.row(currentrow)[curelem]));
		++curelem;
	}

	return ret;
}
//