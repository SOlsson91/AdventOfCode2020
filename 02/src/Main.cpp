#include <iostream>
#include "Utility.h"
#include "Timer.h"
#include <regex>
#include <algorithm>

struct PasswordData
{
	int minTimes;
	int maxTimes;
	std::string character;
	std::string password;
};

bool CheckIfValid(PasswordData data)
{
	int occurrences = std::count(std::begin(data.password), std::end(data.password), *data.character.c_str());

	if (occurrences >= data.minTimes && occurrences <= data.maxTimes)
		return true;
	return false;
}

bool CheckIfValidPartTwo(PasswordData data)
{
	if ((data.password[data.minTimes - 1] == *data.character.c_str()) ^ (data.password[data.maxTimes -1] == *data.character.c_str()))
		return true;
	return false;
}

void FirstStar(std::vector<std::string> data)
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

			if(CheckIfValid(passwordData))
				validPasswords++;
		}
	}

	std::cout << "Valid passwords = " << validPasswords << "\n";
}

void SecondStar(std::vector<std::string> data)
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

			if(CheckIfValidPartTwo(passwordData))
				validPasswords++;
		}
	}

	std::cout << "Valid passwords = " << validPasswords << "\n";
}

int main()
{
	std::vector<std::string> data = Utility::ReadFromFileToString("../input.txt");
	FirstStar(data);
	SecondStar(data);
}

