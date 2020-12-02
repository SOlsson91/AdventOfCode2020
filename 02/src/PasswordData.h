#include <string>
#include <algorithm>

struct PasswordData
{
	int minTimes;
	int maxTimes;
	std::string character;
	std::string password;

	bool CheckIfValidPartOne()
	{
		int occurrences = std::count(std::begin(password), std::end(password), *character.c_str());

		if (occurrences >= minTimes && occurrences <= maxTimes)
			return true;
		return false;
	}

	bool CheckIfValidPartTwo()
	{
		if ((password[minTimes - 1] == *character.c_str()) ^ (password[maxTimes -1] == *character.c_str()))
			return true;
		return false;
	}
};
