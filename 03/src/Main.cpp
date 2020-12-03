#include <iostream>
#include "Utility.h"
#include "Timer.h"

struct V2
{
	int x;
	int y;
	void Print()
	{
		std::cout << "[" << x << ", " << y << "]\n";
	}

	V2& operator+=(const V2& rhs)
	{
		x = x + rhs.x;
		y = y + rhs.y;
		return *this;
	}
};

typedef std::vector<std::vector<std::string>> Map;

Map CreateMap(std::vector<std::string> fileInput)
{
	Map map;
	for (auto row : fileInput)
	{
		std::vector<std::string> rowVector;
		for (auto item : row)
		{
			rowVector.push_back(std::string(1, item));
		}
		map.push_back(rowVector);
	}
	return map;
}

int WalkDownMap(const Map& map, V2 direction)
{
	V2 position = {0, 0};
	int treeHits = 0;

	for (size_t row = 0; row < map.size();)
	{
		if (position.x >= static_cast<int>(map[row].size()))
			position.x = position.x % map[row].size();

		if (map[position.y][position.x] == "#")
			treeHits++;
		
		position += direction;
		row += direction.y;
	}

	return treeHits;
}

unsigned int PartOne(const Map& map)
{
	Timer t;
	V2 direction = {3, 1};
	return WalkDownMap(map, direction);
}

unsigned long PartTwo(const Map& map)
{
	Timer t;
	V2 directions[5] = {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};
	unsigned long solution = 1;

	for (V2 dir : directions)
	{
		solution *= WalkDownMap(map, dir);
	}

	return solution;
}

int main()
{
	std::vector<std::string> fileInput = Utility::ReadFromFileToString("../input.txt");
	Map map = CreateMap(fileInput);

	std::cout << "Part 1 = " << PartOne(map) << "\n";
	std::cout << "Part 2 = " << PartTwo(map) << "\n";
}
