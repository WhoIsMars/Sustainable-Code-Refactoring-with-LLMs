#include "leap.h"

namespace leap
{
	inline bool evenly_divisible_by(const int value, const int divisor) noexcept
	{
		return value % divisor == 0;
	}

	bool is_leap_year(const int year) noexcept
	{
		return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
	}
} // namespace leap