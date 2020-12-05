#include <iostream>
#include <algorithm>
#include "Utility.h"
#include "Timer.h"

int CalculateSeat(const std::string& line, int min, int max)
{
	for (unsigned int i = 0; i <= line.size(); i++)
	{
		if (i == line.size())
			return (line[i] == 'F' || line[i] == 'L') ? min : max;

		if (line[i] == 'F' || line[i] == 'L')
		{
			max = max - (max - min) / 2.0f;
		}
		else if (line[i] == 'B' || line[i] == 'R')
		{
			min = min + (max - min) / 2.0f + 1;
		}
	}
	return -1;
}

int PartOne(const std::vector<std::string>& data, std::vector<int>& seats)
{
	Timer t;
	int highestId = 0;
	for (auto line : data)
	{
		int row = CalculateSeat(line.substr(0, 7), 0, 127);
		if (row == -1)
		{
			std::cout << "[Error] Could not get Row\n";
			return -1;
		}

		int column = CalculateSeat(line.substr(7, 10), 0, 7);
		if (column == -1)
		{
			std::cout << "[Error] Could not get Column\n";
			return -1;
		}

		int seatId = (row * 8) + column;
		seats.push_back(seatId);

		highestId = std::max(seatId, highestId);
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
	std::cout << "Part 1 = " << PartOne(data, seats) << "\n";
	std::cout << "Part 2 = " << PartTwo(seats) << "\n";
}
