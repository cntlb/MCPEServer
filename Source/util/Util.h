#pragma once

#include <string>
#include <algorithm>
#include <functional>
#include <cctype>

class Util
{
public:
	static std::string &toLower(std::string &str)
	{
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		return str;
	}

	// trim from start
	static std::string &ltrim(std::string &s)
	{
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		return s;
	}

	// trim from end
	static std::string &rtrim(std::string &s)
	{
		s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		return s;
	}

	// trim from both ends
	static std::string &trim(std::string &s)
	{
		return ltrim(rtrim(s));
	}
};

