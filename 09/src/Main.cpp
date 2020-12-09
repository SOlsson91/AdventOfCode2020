#include "Utility.h"
#include <algorithm>
#include <list>


bool CheckIfSum(int numToMatch, std::vector<long long> numbers)
{
	for (auto num : numbers)
	{
		for (unsigned int i = 0; i < numbers.size(); i++)
		{
			if (num + numbers[i] == numToMatch)
			{
				return true;
			}
		}
	}
	return false;
}

long long PartOne(int numbersToCheck, const std::vector<long long>& data)
{
	Timer t;

	for (unsigned int i = numbersToCheck; i < data.size(); i++)
	{
		std::vector<long long> subVector(std::begin(data) + i - numbersToCheck, std::begin(data) + i);
		if (!CheckIfSum(data[i], subVector))
			return data[i];
	}
	return -1;
}

long long PartTwo(long long numberToMatch, const std::vector<long long>& data)
{
	Timer t;
	std::vector<long long> subVector(std::begin(data), std::find(std::begin(data), std::end(data), numberToMatch));
	std::list<long long> encryptionWeakness;
	long long sum = 0;
	for (unsigned int i = 0; i < subVector.size(); i++)
	{
		sum += subVector[i];
		encryptionWeakness.push_back(subVector[i]);

		while (sum > numberToMatch)
		{
			sum -= encryptionWeakness.front();
			encryptionWeakness.pop_front();
		}

		if (sum == numberToMatch)
			break;
	}

	return *std::min_element(std::begin(encryptionWeakness), std::end(encryptionWeakness)) +
		   *std::max_element(std::begin(encryptionWeakness), std::end(encryptionWeakness));
}

int main()
{
	auto data = Utility::ReadFromFileToNum<long long>("../input.txt");
	std::cout << "Part 1 = ";
	long long p1 = PartOne(25, data);
	std::cout << p1 << "\n";
	std::cout << "Part 2 = " << PartTwo(p1, data) << "\n";
}
