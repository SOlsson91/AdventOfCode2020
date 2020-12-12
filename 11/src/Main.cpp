#include "Utility.h"
#include <algorithm>

auto CreateMap(const std::vector<std::string>& data)
{
	std::vector<std::vector<char>> seats;
	for (unsigned int i = 0; i < data.size(); i++)
	{
		std::vector<char> line;
		for (char c : data[i])
			line.push_back(c);
		seats.push_back(line);
	}
	return seats;
}

int CountOccupied(int row, int col, const std::vector<std::vector<char>>& seats)
{
	int occupied = 0;
	if (row - 1 >= 0 && seats[row - 1][col] == '#')
		occupied++;
	if (row + 1 < static_cast<int>(seats.size()) && seats[row + 1][col] == '#')
		occupied++;
	if (col + 1 < static_cast<int>(seats[row].size()) && seats[row][col + 1] == '#')
		occupied++;
	if (col - 1 >= 0 && seats[row][col - 1] == '#')
		occupied++;

	if (row - 1 >= 0 && col - 1 >= 0 && seats[row - 1][col - 1] == '#')
		occupied++;
	if (row + 1 < static_cast<int>(seats.size()) && col - 1 >= 0 && seats[row + 1][col - 1] == '#')
		occupied++;
	if (row - 1 >= 0 && col + 1 < static_cast<int>(seats[row].size()) && seats[row - 1][col + 1] == '#')
		occupied++;
	if (row + 1 < static_cast<int>(seats.size()) && col + 1 < static_cast<int>(seats[row].size()) && seats[row + 1][col + 1] == '#')
		occupied++;

	return occupied;
}

bool CheckDirection(int row, int col, const std::vector<std::vector<char>>& seats, std::pair<int, int> dir)
{
	if (row < 0 || row >= static_cast<int>(seats.size()) || col < 0 || col >= static_cast<int>(seats[row].size()))
		return false;

	if (seats[row][col] == '#')
		return true;
	if (seats[row][col] == 'L')
		return false;

	return CheckDirection(row + dir.first, col + dir.second, seats, dir);
}

std::vector<std::pair<int, int>> Directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

int CountOccupiedCorrect(int row, int col, const std::vector<std::vector<char>>& seats)
{
	int count = 0;
	for (auto dir : Directions)
	{
		if (CheckDirection(row + dir.first, col + dir.second, seats, dir))
			count++;
	}

	return count;
}

bool UpdateMap(std::vector<std::vector<char>>& seats)
{
	auto updatedSeats = seats;
	bool updated = false;

	for (unsigned int row = 0; row < seats.size(); row++)
	{
		for (unsigned int col = 0; col < seats[row].size(); col++)
		{
			if (seats[row][col] == 'L' && CountOccupied(row, col, seats) == 0)
			{
				updatedSeats[row][col] = '#';
				updated = true;
			}
			else if (seats[row][col] == '#' && CountOccupied(row, col, seats) >= 4)
			{
				updatedSeats[row][col] = 'L';
				updated = true;
			}
		}
	}
	seats = updatedSeats;
	return updated;
}

bool UpdateMapCorrect(std::vector<std::vector<char>>& seats)
{
	auto updatedSeats = seats;
	bool updated = false;

	for (unsigned int row = 0; row < seats.size(); row++)
	{
		for (unsigned int col = 0; col < seats[row].size(); col++)
		{
			if (seats[row][col] == 'L' && CountOccupiedCorrect(row, col, seats) == 0)
			{
				updatedSeats[row][col] = '#';
				updated = true;
			}
			else if (seats[row][col] == '#' && CountOccupiedCorrect(row, col, seats) >= 5)
			{
				updatedSeats[row][col] = 'L';
				updated = true;
			}
		}
	}
	seats = updatedSeats;
	return updated;
}

int CountOccupiedSeats(const std::vector<std::vector<char>>& seats)
{
	int occupied = 0;
	for (auto row : seats)
	{
		for (auto pos : row)
		{
			if (pos == '#')
				occupied++;
		}
	}
	return occupied;
}

int PartOne(std::vector<std::string>& data)
{
	Timer t;
	auto seats = CreateMap(data);
	while(UpdateMap(seats));
	return CountOccupiedSeats(seats);
}

int PartTwo(std::vector<std::string>& data)
{
	Timer t;
	auto seats = CreateMap(data);
	while(UpdateMapCorrect(seats));
	return CountOccupiedSeats(seats);
}

int main()
{
	std::vector<std::string> data = Utility::ReadFromFileToString("../input.txt");
	std::cout << "Part 1 = " << PartOne(data) << std::endl;
	std::cout << "Part 2 = " << PartTwo(data) << std::endl;
}
