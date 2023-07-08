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