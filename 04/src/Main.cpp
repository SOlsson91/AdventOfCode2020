#include <iostream>
#include <regex>
#include "Utility.h"
#include "Timer.h"

struct PassportData
{
	int byr = -1;
	int iyr = -1;
	int eyr = -1;
	std::string hgt = "";
	std::string hcl = "";
	std::string ecl = "";
	std::string pid = "";
	int cid = -1;

	void Print()
	{
		std::cout << "byr: " << byr << "\n"
				<< "iyr: " << iyr << "\n"
				<< "eyr: " << eyr << "\n"
				<< "hgt: " << hgt << "\n"
				<< "hcl: " << hcl << "\n"
				<< "ecl: " << ecl << "\n"
				<< "pid: " << pid << "\n"
				<< "cid: " << cid << "\n";
	}

	bool IsNumber(const std::string& s)
	{
		return (atoi(s.c_str()));
	}

	bool CheckIfValid()
	{
		if (byr != -1 && iyr != -1 && eyr != -1 && hgt != ""
				&& hcl != "" && ecl != "" && pid != "")
		{
			return true;
		}
		return false;
	}

	bool YearCheck()
	{
		if ((byr >= 1920 && byr <= 2002) && (iyr >= 2010 && iyr <=2020) 
				&& (eyr >= 2010 && eyr <= 2030))
			return true;
		return false;
	}

	bool CheckHeight()
	{
		std::regex rgx("^([0-9]\\d{1,3})([cm|in]\\w)$");
		std::smatch match;
		std::regex_search(hgt, match, rgx);
		if (!match.empty())
		{
			if ((match[2] == "cm" && std::stoi(match[1]) >= 150 && std::stoi(match[1]) <= 193) ||
				(match[2] == "in" && std::stoi(match[1]) >= 59 && std::stoi(match[1]) <= 76))
			{
				return true;
			}
		}
		return false;
	}

	bool CheckHair()
	{
		std::regex rgx("^#[0-9a-f]{6}$");
		std::smatch match;
		std::regex_search(hcl, match, rgx);
		if (!match.empty())
			return true;
		return false;
	}

	bool CheckEyeColor()
	{
		std::regex rgx("^(amb|blu|brn|gry|grn|hzl|oth)$");
		std::smatch match;
		std::regex_search(ecl, match, rgx);
		if (!match.empty())
			return true;
		return false;
	}

	bool CheckPassportLength()
	{
		if (pid.size() == 9)
			return true;
		return false;
	}

	bool CheckIfValidStrict()
	{
		if (!CheckIfValid())
			return false;
		if (YearCheck() && CheckHeight() && CheckHair() && CheckEyeColor() && CheckPassportLength())
			return true;
		return false;
	}
};

std::vector<PassportData> GetDataFromInput(const std::vector<std::string>& input)
{
	std::vector<PassportData> data;
	std::regex regex("((byr|iyr|eyr|hgt|hcl|ecl|pid|cid):([^\n ]+))");
	std::string multiRow;
	for (auto row : input)
	{
		if (row.empty())
		{
			PassportData passportData;
			std::smatch match;
			while (std::regex_search(multiRow, match, regex))
			{
				if (match[2] == "byr")
					passportData.byr = std::stoi(match[3]);
				if (match[2] == "iyr")
					passportData.iyr = std::stoi(match[3]);
				if (match[2] == "eyr")
					passportData.eyr = std::stoi(match[3]);
				if (match[2] == "hgt")
					passportData.hgt = match[3];
				if (match[2] == "hcl")
					passportData.hcl = match[3];
				if (match[2] == "ecl")
					passportData.ecl = match[3];
				if (match[2] == "pid")
					passportData.pid = match[3];
				if (match[2] == "cid")
					passportData.cid = std::stoi(match[3]);
				multiRow = match.suffix();
			}

			data.push_back(passportData);
			multiRow = "";
		}
		else
		{
			multiRow += " " + row;
		}
	}
	return data;
}

int PartOne(const std::vector<PassportData>& data)
{
	Timer t;
	int validPassports = 0;
	for (auto d : data)
	{
		if (d.CheckIfValid())
			validPassports++;
	}
	return validPassports;
}

int PartTwo(const std::vector<PassportData>& data)
{
	Timer t;
	int validPassports = 0;
	for (auto d : data)
	{
		if (d.CheckIfValidStrict())
			validPassports++;
	}
	return validPassports;
}

int main()
{
	std::vector<std::string> input = Utility::ReadFromFileToString("../input.txt");
	std::vector<PassportData> data = GetDataFromInput(input);

	std::cout << "Part 1 = " << PartOne(data) << "\n";
	std::cout << "Part 2 = " << PartTwo(data) << "\n";
}
