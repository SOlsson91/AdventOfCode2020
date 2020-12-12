#include "Utility.h"
#include <list>
#include <cmath>

struct Instruction
{
	char action;
	int value;
	Instruction(char a, int v)
		: action(a), value(v){}
};

template <typename T,typename U>                                                   
std::pair<T,U>& operator+=(std::pair<T,U>& pair, const std::pair<T,U>& rhs) {
	pair.first += rhs.first;
	pair.second += rhs.second;
	return pair;
}

template <typename T,typename U>                                                   
std::pair<T,U> operator*(std::pair<T,U>& lhs, const int& value) {
	std::pair<T, U> ans;
	ans.first = lhs.first * value;
	ans.second = lhs.second * value;
	return ans;
}

std::vector<Instruction> ReadInstructions(const std::vector<std::string>& data)
{
	std::vector<Instruction> instructions;
	for (auto line : data)
	{
		instructions.push_back(Instruction(*line.substr(0,1).c_str(), std::stoi(line.substr(1,line.size()))));
	}
	return instructions;
}

int PartOne(const std::vector<std::string>& data)
{
	Timer t;
	auto instructions = ReadInstructions(data);
	std::list<std::pair<int, int>> directions = {{1,0}, {0, -1}, {-1, 0}, {0, 1}}; // E, S, W, N
	std::list<std::pair<int, int>>::iterator facing = directions.begin();

	std::pair<int, int> position = {0, 0};

	for (auto ins : instructions)
	{
		if (ins.action == 'N')
			position += {0, ins.value};
		else if (ins.action == 'S')
			position += {0, -ins.value};
		else if (ins.action == 'W')
			position += {-ins.value, 0};
		else if (ins.action == 'E')
			position += {ins.value, 0};

		else if (ins.action == 'F')
			position += (*facing) * ins.value;
		else if (ins.action == 'L')
		{
			int steps = ins.value / 90;
			for (int i = 0; i < steps; i++)
			{
				facing = facing == directions.begin() ? std::prev(directions.end()) : std::prev(facing);
			}
		}
		else if (ins.action == 'R')
		{
			int steps = ins.value / 90;
			for (int i = 0; i < steps; i++)
			{
				facing = std::next(facing) == directions.end() ? directions.begin() : std::next(facing);
			}
		}
	}
	return std::abs(position.first) + std::abs(position.second);
}

void RotateAroundWaypoint(std::pair<int, int>& waypoint, int rotation)
{
	auto tmp = waypoint;
	double theta = static_cast<double>(rotation) * M_PI / 180.0;
	waypoint.first = static_cast<int>(std::round(tmp.first * std::cos(theta) - tmp.second * std::sin(theta)));
	waypoint.second = static_cast<int>(std::round(tmp.first * std::sin(theta) + tmp.second * std::cos(theta)));
}

int PartTwo(const std::vector<std::string>& data)
{
	Timer t;
	auto instructions = ReadInstructions(data);
	std::pair<int, int> position = {0, 0};
	std::pair<int, int> waypoint = {10, 1};

	for (auto ins : instructions)
	{
		if (ins.action == 'N')
			waypoint.second += ins.value;
		else if (ins.action == 'S')
			waypoint.second -= ins.value;
		else if (ins.action == 'E')
			waypoint.first += ins.value;
		else if (ins.action == 'W')
			waypoint.first -= ins.value;

		else if (ins.action == 'F')
			position += waypoint * ins.value;
		else if (ins.action == 'L')
			RotateAroundWaypoint(waypoint, ins.value);
		else if (ins.action == 'R')
			RotateAroundWaypoint(waypoint, -ins.value);
	}

	return std::abs(position.first) + std::abs(position.second);
}

int main()
{
	auto data = Utility::ReadFromFileToString("../input.txt");
	std::cout << "Part 1 = " << PartOne(data) << "\n";
	std::cout << "Part 2 = " << PartTwo(data) << "\n";
}
