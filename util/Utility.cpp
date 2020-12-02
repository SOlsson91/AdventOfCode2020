#include "Utility.h"

std::vector<int> Utility::ReadFromFileToInt(const std::string& inputFile)
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

std::vector<std::string> Utility::ReadFromFileToString(const std::string& inputFile)
{
	std::vector<std::string> data;

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
			data.push_back(row);
		}
		file.close();
	}
	return data;
}
