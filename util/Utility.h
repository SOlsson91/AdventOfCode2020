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
	static std::vector<int> ReadFromFileToInt(const std::string& file);
	static std::vector<std::string> ReadFromFileToString(const std::string& file);
	static std::vector<std::string> SplitString(const std::string& line);
};
