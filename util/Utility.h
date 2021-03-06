#pragma once 

#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include "Timer.h"

class Utility
{
public:
	template <typename T>
	static std::vector<T> ReadFromFileToNum(const std::string& inputFile)
	{
		std::vector<T> data;

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
				data.push_back(std::stoll(row));
			}
			file.close();
		}
		return data;
	}

	static std::vector<int> ReadFromFileToInt(const std::string& file);
	static std::vector<std::string> ReadFromFileToString(const std::string& file);
	static std::vector<std::string> SplitString(const std::string& line);
};
