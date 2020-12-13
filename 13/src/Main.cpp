#include "Utility.h"
#include <algorithm>
#include <numeric>

std::vector<int> GetBusses(const std::string& data)
{
	std::vector<int> busses;
	std::stringstream ss(data);
	std::string s;
	while (std::getline(ss, s, ','))
	{
		if (s != "x")
			busses.push_back(std::stoi(s));
	}
	return busses;
}

std::vector<std::pair<int, int>> GetBussesWithOrder(const std::string& data)
{
	std::vector<std::pair<int, int>> busses;
	std::stringstream ss(data);
	std::string s;
	int i = 0;
	while (std::getline(ss, s, ','))
	{
		if (s != "x")
			busses.push_back({std::stoi(s), i});
		i++;
	}
	return busses;
}

int PartOne(const std::vector<std::string>& data)
{
	Timer t;
	int earliestDepartureTime = std::stoi(data[0]);
	std::vector<int> busses = GetBusses(data[1]);

	std::pair<int, int> bestBuss = {-1, INT8_MAX};

	for (auto buss : busses)
	{
		int minutesRemaining = earliestDepartureTime % buss;

		if ((earliestDepartureTime / buss) * buss < earliestDepartureTime)
			minutesRemaining = buss - minutesRemaining;

		if (minutesRemaining < bestBuss.second)
			bestBuss = std::make_pair(buss, minutesRemaining);
	}

	return bestBuss.first * bestBuss.second;
}

long int PartTwo(const std::vector<std::string>& data)
{
	Timer tim;
	std::vector<std::pair<int, int>>busses = GetBussesWithOrder(data[1]);

	long int t = busses[0].first - busses[0].second;
	long int step = busses[0].first;

	for (auto buss : busses)
	{
		while (true)
		{
			if ((t + buss.second) % buss.first == 0)
				break;
			t += step;
		}
		step = std::lcm(step, buss.first);
	}
	return t;
}

int main()
{
	std::vector<std::string> data = Utility::ReadFromFileToString("../input.txt");
	std::cout << "Part 1 = " << PartOne(data) << "\n";
	std::cout << "Part 2 = " << PartTwo(data) << "\n";
}
