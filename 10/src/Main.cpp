#include "Utility.h"
#include <algorithm>
#include <map>

int PartOne(std::vector<int>& data)
{
	Timer t;
	std::sort(std::begin(data), std::end(data));

	std::map<int, int> differences{{1, 0}, {2, 0}, {3, 0}};

	for (unsigned int i = 0; i < data.size(); i++)
	{
		if (i + 1 < data.size())
			differences[data[i + 1] - data[i]] += 1;
	}

	differences[3] += 1; // Always end with a three diff
	return differences[1] * differences[3];
}

long int PartTwo(std::vector<int>& data)
{
	Timer t;
	std::sort(std::begin(data), std::end(data));
	std::vector<long int> differences(data.size(), 0);
	differences[0] = 1;

	for (unsigned int i = 0; i < data.size(); i++)
	{
		for (unsigned int j = i + 1; j < data.size(); j++)
		{
			if (data[j] - data[i] > 3)
				break;
			differences[j] += differences[i];
		}
	}

	return differences[differences.size()- 1];
}

int main()
{
	std::vector<int> data = Utility::ReadFromFileToInt("../input.txt");
	data.push_back(0); //Always start with zero but data does not

	std::cout << "Part 1 = " << PartOne(data) << "\n";
	std::cout << "Part 2 = " << PartTwo(data) << "\n";

}
