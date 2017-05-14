#include<cmath>
#include<iostream>
#include<vector>
#include<utility>
#include<array>


int main()
{
	std::vector<std::pair<double, std::array<unsigned char, 4>>> vals;
	std::cout << "enter value to approximate: ";
	double approximation_target;
	std::cin >> approximation_target;
	unsigned char extent;
	unsigned short extval;
	std::cout << "enter the maximum number allowed: ";
	std::cin >> extval;
	extent = 1 + unsigned char(extval);

	unsigned char min = 1;


	vals.reserve(std::pow(extent,4));

	for (unsigned char num = min; num != extent; ++num)
	{
		for (unsigned char den = min; den != extent; ++den)
		{
			for (unsigned char numexp = min; numexp != extent; ++numexp)
			{
				for (unsigned char denexp = min; denexp != extent; ++denexp)
				{
					vals.push_back({ std::pow((double(num) / double(den)),(double(numexp) / double(denexp))), {num,den,numexp,denexp} });
				}
			}
		}
	}

	double smallest_diff = INFINITY;
	double closest_val;
	std::array<unsigned char, 4> closest_wrt;

	for (int i = 0; i != vals.size(); ++i)
	{
		double diff = std::abs(vals[i].first - approximation_target);
		if (smallest_diff > diff)
		{
			smallest_diff = diff;
			closest_val = vals[i].first;
			closest_wrt = vals[i].second;
		}

	}
	std::cout << std::endl;
	std::cout << "expression: (" << int(closest_wrt[0]) << "/" << int(closest_wrt[1]) << ")^(" << int(closest_wrt[2]) << "/" << int(closest_wrt[3]) << ")" << std::endl;
	std::cout << "decimal approximationm of expression: " << closest_val << std::endl;
	std::cout << "approximate difference of expression aproximation and origional target: " << smallest_diff << std::endl << std::endl;
	
	return(main());
}
