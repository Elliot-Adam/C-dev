#pragma once
#include <string>
#include <vector>
class Utility
{
public:
	static bool MakePair(const std::string& src, char separator, std::string& lhs, std::string& rhs);
	static std::vector<std::string> Split(const std::string& source,const std::string& sep);
};
