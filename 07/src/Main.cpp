#include "Utility.h"

struct Bag
{
	std::string name;
	std::vector<Bag*> bags;
	std::vector<int> amount;

	Bag(std::string n)
	{
		this->name = n;
	}
};

Bag* FindBag(const std::string& name, std::map<std::string, Bag*>& map)
{
	if (map.find(name) == map.end())
	{
		map[name] = new Bag(name);
	}
	return map[name];
}

bool CanContainBag(const std::string& name, Bag* bag)
{
	if (bag->name == name)
		return true;

	for (unsigned int i = 0; i < bag->bags.size(); i++)
	{
		if (CanContainBag(name, bag->bags[i]))
			return true;
	}
	return false;
}

int CountInternalBags(Bag* bag)
{
	int result = 0;

	for (unsigned int i = 0; i < bag->amount.size(); i++)
	{
		result += bag->amount[i] + (bag->amount[i] * CountInternalBags(bag->bags[i]));
	}
	return result;
}

int PartOne(const std::string& bagName, const std::map<std::string, Bag*>& bags)
{
	Timer t;
	int shinyBag = 0;
	for (auto bag : bags)
	{
		if (bag.first != bagName && CanContainBag(bagName, bag.second))
			shinyBag++;
	}

	return shinyBag;
}

int PartTwo(const std::string& bagName, std::map<std::string, Bag*>& bags)
{
	Timer t;
	return CountInternalBags(FindBag(bagName, bags));
}

void CreateMap(const std::vector<std::string>& data, std::map<std::string, Bag*>& bags)
{
	Timer t;
	for (auto line : data)
	{
		std::vector<std::string> splitLine = Utility::SplitString(line);

		Bag* bag = FindBag(splitLine[0] + " " + splitLine[1], bags);

		for (unsigned int i = 4; i < splitLine.size(); i += 4)
		{
			int numberOfBags = std::atoi(splitLine[i].c_str());
			if (numberOfBags <= 0)
				continue;

			Bag* insideBags = FindBag(splitLine[i + 1] + " " + splitLine[i + 2], bags);
			bag->bags.push_back(insideBags);
			bag->amount.push_back(numberOfBags);
		}
	}
}

int main()
{
	std::vector<std::string> data = Utility::ReadFromFileToString("../input.txt");
	std::map<std::string, Bag*> bags;

	std::cout << "Setup Time = ";
	CreateMap(data, bags);
	std::cout << "\n";
	std::cout << "Part 1 = " << PartOne("shiny gold", bags) << "\n";
	std::cout << "Part 2 = " << PartTwo("shiny gold", bags) << "\n";
}
