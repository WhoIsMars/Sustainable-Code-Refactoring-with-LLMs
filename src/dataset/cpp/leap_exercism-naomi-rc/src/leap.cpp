#include "leap.h"

namespace leap {
	bool is_leap_year(int year) {
		return is_divisible(year, 4) && (!is_divisible(year, 100) || is_divisible(year, 400));
	}

	bool is_divisible(int year, int dividend){
		return year % dividend == 0;
	}
}  // namespace leap
