#include "binary.h"

int binary::convert(std::string s)
{
	auto result = 0;
	for (auto ch : s)
	{
		result <<= 1;
		if (ch == '1')
			result |= 1;
		else if (ch != '0')
			return 0;
	}
	return result;
}