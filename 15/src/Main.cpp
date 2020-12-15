#include "Utility.h"
#include <unordered_map>

std::vector<int> GetNumbers(const std::string& data)
{
	std::vector<int> numbers;
	std::stringstream ss(data);
	std::string s;
	while (std::getline(ss, s, ','))
	{
		if (s != "x")
			numbers.push_back(std::stoi(s));
	}
	return numbers;
}

int PlayGame(const std::vector<int>& data, unsigned int depth)
{
	Timer t;
	std::unordered_map<int, int> memory;

	for (unsigned int turn = 0; turn < data.size(); turn++)
		memory[data[turn]] = turn;

	int prevTurn = data[data.size() - 1];
	for (unsigned int turn = data.size(); turn < depth; turn++)
	{
		int current;
		if (memory.find(prevTurn) == memory.end())
			current = 0;
		else
			current = turn - 1 - memory[prevTurn];

		memory[prevTurn] = turn - 1;
		prevTurn = current;
	}
	return prevTurn;
}

int main()
{
	std::string input = "0,3,1,6,7,5";
	std::vector<int> data = GetNumbers(input);
	std::cout << "Part 1 = " << PlayGame(data, 2020) << "\n";
	std::cout << "Part 2 = " << PlayGame(data, 30'000'000) << "\n";
}
