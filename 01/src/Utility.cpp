#include "Utility.h"

std::vector<int> Utility::ReadFromFile(std::string inputFile)
{
	std::vector<int> data;

	std::fstream file;
	file.open(inputFile, std::ios::in);
	if (!file)
	{
		std::cout << "Error opening file \n";
	}
	else
	{
		std::string row;
		while (getline(file, row))
		{
			data.push_back(std::stoi(row));
		}
		file.close();
	}
	return data;
}
