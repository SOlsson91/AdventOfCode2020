#include "Utility.h"
#include <regex>

struct Field
{
	std::string name;
	std::pair<int, int> range1;
	std::pair<int, int> range2;
	Field(const std::string& s, std::pair<int, int> r1, std::pair<int, int> r2)
		: name(s), range1(r1), range2(r2)
	{}

	bool IsValid(int value)
	{
		if (((value >= range1.first) && (value <= range1.second)) ||
			((value >= range2.first) && (value <= range2.second)))
			return true;
		return false;
	}
};

int main()
{
	std::vector<std::string> data = Utility::ReadFromFileToString("../input_test.txt");
	std::regex regexField("([a-z\\s]+): (\\d+)-(\\d+) or (\\d+)-(\\d+)");
	std::regex regexNumbers("(\\d+)");
	std::smatch match;
	std::vector<Field> fields;
	std::vector<std::vector<int>> tickets;

	unsigned int i = 0;
	for (; i < data.size(); i++)
	{
		if (data[i].empty())
			break;

		std::regex_search(data[i], match, regexField);
		fields.push_back(Field(match[1], { std::stoi(match[2]), std::stoi(match[3]) }, { std::stoi(match[4]), std::stoi(match[5]) }));
	}
	i++;

	for (; i < data.size(); i++)
	{
		if (data[i].empty() || data[i][0] == 'y' || data[i][0] == 'n')
			continue;

		std::vector<int> ticket;
		std::smatch smatch;

		std::regex_search(data[i], smatch, regexNumbers);
		for (std::sregex_iterator it = std::sregex_iterator(std::begin(data[i]), std::end(data[i]), regexNumbers);
			it != std::sregex_iterator();
			it++)
		{
			std::smatch m = *it;
			ticket.push_back(std::stoi(m.str()));
		}

		if (ticket.size() > 0)
			tickets.push_back(ticket);
	}

	int result = 0;
	for (auto ticket : tickets)
	{
#if 0
		for (auto num : ticket)
		{
			for (auto& field : fields)
			{
			}
		}
#endif
	}
	std::cout << result << std::endl;
#if 0
	for (auto t : tickets)
	{
		for (auto ti : t)
			std::cout << ti << ",";
		std::cout << std::endl;
	}
#endif
}
