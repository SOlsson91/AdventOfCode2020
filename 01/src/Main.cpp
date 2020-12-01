#include "Utility.h"
#include <iostream>
#include <algorithm>

void FirstStar(std::vector<int>& data)
{
	std::cout << "Part 1: \n";
	for (auto v1 : data)
	{
		for (auto v2 : data)
		{
			if ( v1 + v2 == 2020)
			{
				std::cout << v1 << " + " << v2 << " = " << v1 + v2 << "\n";
				std::cout << v1 * v2 << "\n";
				return;
			}
		}
	}
}

void SecondStar(std::vector<int>& data)
{
	std::cout << "Part 2: \n";
	for (auto v1 : data)
	{
		for (auto v2 : data)
		{
			for (auto v3 : data)
			{
				if ( v1 + v2 + v3 == 2020)
				{
					std::cout << v1 << " + " << v2 << " + " << v3 << " = " << v1 + v2 + v3 << "\n";
					std::cout << v1 * v2 * v3 << "\n";
					return;
				}
			}
		}
	}
}

int main()
{
	std::vector<int> data = Utility::ReadFromFile("../input.txt");

	FirstStar(data);
	SecondStar(data);
}
