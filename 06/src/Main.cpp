#include <iostream>
#include "Utility.h"
#include "Timer.h"
#include <map>

int PartOne(const std::vector<std::string>& data)
{
	Timer t;
	std::map<char, int> group;
	int questionsAnswered = 0;

	for (auto line : data)
	{
		if (line == "")
		{
			questionsAnswered += group.size();
			group.clear();
			continue;
		}
		for (auto c : line)
			group.insert({c, 1});
	}
	questionsAnswered += group.size();
	return questionsAnswered;
}

int GetAnswersFromGroup(const std::map<char, int>& group, const int& groupSize)
{
	int answers = 0;
	for (auto answer : group)
	{
		if (answer.second == groupSize)
			answers++;
	}
	return answers;
}

int PartTwo(const std::vector<std::string>& data)
{
	Timer t;
	std::map<char, int> group;
	int groupSize = 0;
	int questionsAnswered = 0;

	for (auto line : data)
	{
		if (line == "")
		{
			questionsAnswered += GetAnswersFromGroup(group, groupSize);
			group.clear();
			groupSize = 0;
			continue;
		}

		groupSize++;
		for (auto c : line)
		{
			if (group.find(c) == group.end())
				group.insert({c, 1});
			else
				group.insert({c, group.at(c)++});
		}
	}

	questionsAnswered += GetAnswersFromGroup(group, groupSize);

	return questionsAnswered;
}

int main ()
{
	std::vector<std::string> data = Utility::ReadFromFileToString("../input.txt");
	std::cout << "Part 1: " << PartOne(data) << "\n";
	std::cout << "Part 2: " << PartTwo(data) << "\n";
}
