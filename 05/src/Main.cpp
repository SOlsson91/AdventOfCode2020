#include <iostream>
#include <cmath>
#include <algorithm>
#include "Utility.h"
#include "Timer.h"

int PartOne(const std::vector<std::string>& data, std::vector<int>& seats)
{
	Timer t;
	int highestId = 0;
	for (auto line : data)
	{
		int min = 0;
		int max = 127;
		int row = 0;
		for (unsigned long i = 0; i < line.size() - 3; i++)
		{
			if (i == line.size() - 4)
			{
				row = (line[i] == 'F') ? min : max;
				break;
			}
			if (line[i] == 'F')
			{
				int temp = std::ceil((max - min) / 2.0f);
				max = max - temp;
			}
			else if (line[i] == 'B')
			{
				int temp = std::ceil((max - min) / 2.0f);
				min = min + temp;
			}
		}

		int column = 0;
		min = 0;
		max = 7;
		for (unsigned long i = line.size() - 3; i <= line.size(); i++)
		{
			if (i == line.size())
			{
				column = (line[i] == 'L') ? min : max;
				break;
			}
			if (line[i] == 'L')
			{
				int temp = std::ceil((max - min) / 2.0f);
				max = max - temp;
			}
			else if (line[i] == 'R')
			{
				int temp = std::ceil((max - min) / 2.0f);
				min = min + temp;
			}
		}

		int result = (row * 8) + column;
		seats.push_back(result);
		if (result > highestId)
			highestId = result;
	}

	return highestId;
}

int PartTwo(std::vector<int>& seats)
{
	Timer t;
	std::sort(std::begin(seats), std::end(seats));
	int i = seats[0];
	for (auto seat : seats)
	{
		if (seat != i)
			return seat - 1;
		i++;
	}
	return -1;
}

int main()
{
	std::vector<std::string> data = Utility::ReadFromFileToString("../input.txt");
	std::vector<int> seats;
	std::cout << "Part One = " << PartOne(data, seats) << "\n";
	std::cout << "Part Two = " << PartTwo(seats) << "\n";
}
