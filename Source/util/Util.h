#pragma once

#include <string>
#include <algorithm>
#include <functional>
#include <cctype>

class Util
{
public:
	static std::string toLower(std::string const &str)
	{
		std::string temp = str;
		std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		return temp;
	}

	// trim from start
	static std::string ltrim(std::string const &s)
	{
		std::string temp = s;
		temp.erase(temp.begin(), std::find_if(temp.begin(), temp.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		return temp;
	}

	// trim from end
	static std::string rtrim(std::string const &s)
	{
		std::string temp = s;
		temp.erase(std::find_if(temp.rbegin(), temp.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), temp.end());
		return temp;
	}

	// trim from both ends
	static std::string trim(std::string const &s)
	{
		return ltrim(rtrim(s));
	}
};

