#include "Utility.h"

int CheckCommand(const std::pair<std::string, int>& cmd, int& index)
{
	if (cmd.first == "nop")
	{
		index++;
	}
	else if (cmd.first == "acc")
	{
		index++;
		return cmd.second;
	}
	else if (cmd.first == "jmp")
	{
		index += cmd.second;
	}
	return 0;
}

int PartOne(const std::vector<std::string>& data)
{
	Timer t;
	int accumulator = 0;
	std::vector<int> visited(data.size());
	int i = 0;
	while (true)
	{
		auto lineData = Utility::SplitString(data[i]);

		visited[i] += 1;
		if (visited[i] > 1)
			return accumulator;

		accumulator += CheckCommand({lineData[0], std::atoi(lineData[1].c_str())}, i);
	}
	return 0;
}

int FindInfLoop(const std::vector<std::string>& data)
{
	int accumulator = 0;
	std::vector<int> visited(data.size());
	int i = 0;
	while (true)
	{
		if (i == static_cast<int>(data.size()))
			return accumulator;

		auto lineData = Utility::SplitString(data[i]);

		visited[i] += 1;
		if (visited[i] > 1)
			return -1;

		accumulator += CheckCommand({lineData[0], std::atoi(lineData[1].c_str())}, i);
	}
	return -1;
}

int PartTwo(const std::vector<std::string>& data)
{
	Timer t;
	std::vector<std::string> dataCopy;
	int accumulator = -1;
	for (int i = 0; i < static_cast<int>(data.size()); i++)
	{
		dataCopy = data;
		auto lineData = Utility::SplitString(data[i]);

		if (lineData[0] == "nop")
		{
			dataCopy[i] = "jmp " + lineData[1];
			accumulator = FindInfLoop(dataCopy);
		}
		else if (lineData[0] == "jmp")
		{
			dataCopy[i] = "nop " + lineData[1];
			accumulator = FindInfLoop(dataCopy);
		}

		if (accumulator != -1)
			return accumulator;
	}
	return -1;
}

int main()
{
	std::vector<std::string> data = Utility::ReadFromFileToString("../input.txt");
	std::cout << "Part 1 = " << PartOne(data) << "\n";
	std::cout << "Part 2 = " << PartTwo(data) << "\n";
}
