#include "Utility.h"
#include "Timer.h"
#include <iostream>
#include <algorithm>

void FirstStar(std::vector<int> data)
{
	std::cout << "Part 1: \n";
	Timer t("Part 1");

	std::sort(std::begin(data), std::end(data));
	for(auto v1 : data)
	{
		int v2 = 2020 - v1;
		auto result = std::find(std::begin(data), std::end(data), v2);
		if (result != std::end(data))
		{
			std::cout << v1 << " + " << v2 << " = " << v1 + v2 << "\n";
			std::cout << "Solution = " << v1 * v2 << "\n";
			return;
		}
	}
}

void SecondStar(std::vector<int> data)
{
	std::cout << "Part 2: \n";
	Timer t("Part 2");

	std::sort(std::begin(data), std::end(data));
	for (auto v1 : data)
	{
		for (auto v2 : data)
		{
			if (v1 != v2)
			{
				int v3 = 2020 - v1 - v2;
				auto result = std::find(std::begin(data), std::end(data), v3);
				if (result != std::end(data))
				{
					std::cout << v1 << " + " << v2 << " + " << v3 << " = " << v1 + v2 + v3 << "\n";
					std::cout << "Solution = " << v1 * v2 * v3 << "\n";
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
