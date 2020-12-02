#pragma once 

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class Utility
{
public:
	static std::vector<int> ReadFromFileToInt(const std::string& file);
	static std::vector<std::string> ReadFromFileToString(const std::string& file);
};
