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

	bool IsValid(int value) const
	{
		if (((value >= range1.first) && (value <= range1.second)) ||
			((value >= range2.first) && (value <= range2.second)))
			return true;
		return false;
	}
};


std::vector<Field> GetFields(const std::vector<std::string>& data, unsigned int& index)
{
	std::vector<Field> fields;
	std::smatch match;
	std::regex regexField("([a-z\\s]+): (\\d+)-(\\d+) or (\\d+)-(\\d+)");

	for (; index < data.size(); index++)
	{
		if (data[index].empty())
			break;

		std::regex_search(data[index], match, regexField);
		fields.push_back(Field(match[1], { std::stoi(match[2]), std::stoi(match[3]) }, { std::stoi(match[4]), std::stoi(match[5]) }));
	}
	index++;
	return fields;
}

std::vector<std::vector<int>> GetTickets(const std::vector<std::string>& data, unsigned int& index)
{
	std::vector<std::vector<int>> tickets;
	std::regex regexNumbers("(\\d+)");
	for (; index < data.size(); index++)
	{
		if (data[index].empty() || data[index][0] == 'y' || data[index][0] == 'n')
			continue;

		std::vector<int> ticket;
		std::smatch smatch;

		std::regex_search(data[index], smatch, regexNumbers);
		for (std::sregex_iterator it = std::sregex_iterator(std::begin(data[index]), std::end(data[index]), regexNumbers);
			it != std::sregex_iterator();
			it++)
		{
			std::smatch m = *it;
			ticket.push_back(std::stoi(m.str()));
		}

		if (ticket.size() > 0)
			tickets.push_back(ticket);
	}
	return tickets;
}


std::pair<int, std::vector<bool>> PartOne(const std::vector<std::vector<int>>& tickets, const std::vector<Field>& fields)
{
	Timer t;
	int result = 0;
	std::vector<bool> invalid(tickets.size());
	unsigned int index = 0;
	for (auto ticket : tickets)
	{
		for (auto num : ticket)
		{
			bool valid = false;
			for (auto& field : fields)
			{
				valid = field.IsValid(num);
				if (valid)
					break;
			}

			if (!valid)
			{
				result += num;
				invalid[index] = true;
			}
		}
		index++;
	}
	return std::make_pair(result, invalid);
}

int PartTwo(/*const std::vector<std::vector<int>>& tickets, const std::vector<Field>& fields, const std::vector<bool>& invalids*/)
{
	Timer t;

	return 0;
}

int main()
{
	std::vector<std::string> data = Utility::ReadFromFileToString("../input.txt");

	unsigned int index = 0;
	std::vector<Field> fields = GetFields(data, index);
	std::vector<std::vector<int>> tickets = GetTickets(data, index);

	std::cout << "Part 1 = ";
	auto p1 = PartOne(tickets, fields);
	std::cout << p1.first << "\n";
	//std::cout << "Part 2 = " << PartTwo(tickets, fields, p1.second) << "\n";
}
