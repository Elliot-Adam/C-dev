#include "Utility.h"

bool Utility::MakePair(const std::string& src, char separator, std::string& lhs, std::string& rhs)
{
	size_t index = src.find(separator);
	if (index != std::string::npos)
	{
		lhs.assign(src.c_str(), index);
		rhs.assign(src.begin() + index + 1, src.end());
		return true;
	}
	return false;
}

std::vector<std::string> Utility::Split(const std::string& source,const std::string& sep){
	std::vector<std::string> split;
	std::size_t start = 0;
	std::size_t end = source.find(sep);
	while (end != std::string::npos){
		split.emplace_back(&source[start], end - start);
		start = end + sep.length();
		end = source.find(sep,start);
	}
	split.emplace_back(&source[start]);
	return split;
}