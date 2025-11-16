#include "leap.h"

namespace leap {
	inline bool is_divisible(int year, int dividend) {
		return year % dividend == 0;
	}

	bool is_leap_year(int year) {
		if (year % 4 != 0) return false;
		if (year % 100 == 0 && year % 400 != 0) return false;
		return true;
	}
}  // namespace leap