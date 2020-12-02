#include <iostream>
#include <regex>
#include "Utility.h"
#include "Timer.h"
#include "PasswordData.h"

int FirstStar(std::vector<std::string> data)
{
	Timer t("Part 1:");
	int validPasswords = 0;
	std::regex regex("(\\d+)-(\\d+) (.): (.+)");
	for (auto row : data)
	{
		std::smatch match;
		std::regex_search(row, match, regex);
		if (!match.empty())
		{
			PasswordData passwordData;
			passwordData.minTimes = stoi(match[1]);
			passwordData.maxTimes =  stoi(match[2]);
			passwordData.character = match[3];
			passwordData.password = match[4];

			if(passwordData.CheckIfValidPartOne())
				validPasswords++;
		}
	}
	return validPasswords;
}

int SecondStar(std::vector<std::string> data)
{
	Timer t("Part 2:");
	int validPasswords = 0;
	std::regex regex("(\\d+)-(\\d+) (.): (.+)");
	for (auto row : data)
	{
		std::smatch match;
		std::regex_search(row, match, regex);
		if (!match.empty())
		{
			PasswordData passwordData;
			passwordData.minTimes = stoi(match[1]);
			passwordData.maxTimes =  stoi(match[2]);
			passwordData.character = match[3];
			passwordData.password = match[4];

			if(passwordData.CheckIfValidPartTwo())
				validPasswords++;
		}
	}
	return validPasswords;
}

int main()
{
	std::vector<std::string> data = Utility::ReadFromFileToString("../input.txt");
	std::cout << "Part 1 = " << FirstStar(data) << "\n";
	std::cout << "Part 2 = " << SecondStar(data) << "\n";
}

