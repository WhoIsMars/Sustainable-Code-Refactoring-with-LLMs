#include "binary.h"

int binary::convert(std::string s)
{
	auto result = 0;
	for (auto const ch : s)
	{
		if (ch == '1') {
			result = (result << 1) | 1;
		} else if (ch == '0') {
			result <<= 1;
		} else {
			return 0;
		}
	}
	return result;
}