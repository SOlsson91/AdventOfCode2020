#include "Utility.h"
#include <regex>
#include <bitset>

unsigned long int PartOne(const std::vector<std::string>& data)
{
	Timer t;
	std::map<unsigned long int, unsigned long int> mem;

	unsigned long int orMask = 0;
	unsigned long int andMask = ~orMask;
	unsigned long int one = 1;

	const std::regex reg("([0-9]+)+");
	std::smatch match;

	for (auto row : data)
	{
		std::vector<std::string> line = Utility::SplitString(row);
		if (line[0] == "mask")
		{
			auto memory = line[2];
			orMask = 0;
            andMask = ~orMask;

            for (unsigned int i = 0; i < memory.size(); i++) {
				unsigned int memoryPos = memory.size() - 1 - i;
                if (memory[memoryPos] == '1')
                    orMask += (one << i);
                else if (memory[memoryPos] == '0')
                    andMask -= (one << i);
			}
		}
		else
		{
			std::regex_search(line[0], match, reg);
			unsigned long int memAdd = std::stoul(match[0]);
			unsigned long int num = std::stoul(line[2]);

			mem[memAdd] = (num & andMask) | orMask;
		}
	}

	unsigned long int result = 0;
	for (auto add : mem)
		result += add.second;
	return result;
}

unsigned long int PartTwo(const std::vector<std::string>& data)
{
	Timer t;
	std::map<unsigned long int, unsigned long int> mem;
	std::vector<unsigned long int> addresses;

	unsigned long int orMask = 0;
	unsigned long int andMask = ~orMask;
	unsigned long int eitherMask = 0;
	unsigned long int one = 1;

	const std::regex reg("([0-9]+)+");
	std::smatch match;

	for (auto row : data)
	{
		std::vector<std::string> line = Utility::SplitString(row);
		if (line[0] == "mask")
		{
			auto memory = line[2];
			orMask = 0;
            eitherMask = 0;
            andMask = ~orMask;
            for (unsigned int i = 0; i < memory.size(); i++) {
				unsigned int memoryPos = memory.size() - 1 - i;
                if (memory[memoryPos] == '1')
                    orMask += (one << i);
                else if (memory[memoryPos] == '0')
                    andMask -= (one << i);
                else if (memory[memoryPos] == 'X')
                    eitherMask += (one << i);
			}
		}
		else
		{
			std::regex_search(line[0], match, reg);
			unsigned long int memAdd = std::stoul(match[0]);
			
			addresses.clear();
			addresses.push_back(((memAdd | orMask) & (~eitherMask)));

			for (unsigned long int i = 0; i < 36; i++)
			{
				if (((eitherMask >> i) & one) > 0)
				{
					const unsigned long int MAX = addresses.size();
					for (unsigned long int j = 0; j < MAX; j++)
						addresses.push_back(addresses[j] + (one << i));
				}
			}

			unsigned long int num = std::stoul(line[2]);
			for (auto v : addresses)
				mem[v] = num;
		}
	}

	unsigned long int result = 0;
	for (auto add : mem)
		result += add.second;
	return result;
}

int main()
{
	std::vector<std::string> data = Utility::ReadFromFileToString("../input.txt");
	std::cout << "Part 1 = " << PartOne(data) << "\n";
	std::cout << "Part 2 = " << PartTwo(data) << "\n";
}
