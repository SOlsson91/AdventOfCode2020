#include <iostream>
#include <algorithm>
#include "Utility.h"
#include "Timer.h"

int GetRow(const std::string& line)
{
	int min = 0;
	int max = 127;
	for (unsigned long i = 0; i <= line.size() - 4; i++)
	{
		if (i == line.size() - 4)
		{
			return (line[i] == 'F') ? min : max;
		}
		if (line[i] == 'F')
		{
			max = max - (max - min) / 2.0f;
		}
		else if (line[i] == 'B')
		{
			min = min + (max - min) / 2.0f + 1;
		}
	}
	return -1;
}

int GetColumn(const std::string& line)
{
	int min = 0;
	int max = 7;
	for (unsigned long i = line.size() - 3; i <= line.size(); i++)
	{
		if (i == line.size())
		{
			return (line[i] == 'L') ? min : max;
		}
		if (line[i] == 'L')
		{
			max = max - (max - min) / 2.0f;
		}
		else if (line[i] == 'R')
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
		int row = GetRow(line);
		if (row == -1)
		{
			std::cout << "[Error] Could not get Row\n";
			return -1;
		}

		int column = GetColumn(line);
		if (column == -1)
		{
			std::cout << "[Error] Could not get Column\n";
			return -1;
		}

		int seatId = (row * 8) + column;
		seats.push_back(seatId);

		if (seatId > highestId)
			highestId = seatId;
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
