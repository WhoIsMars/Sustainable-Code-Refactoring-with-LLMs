#include "leap.h"

namespace leap {
	inline bool is_divisible(int year, int dividend) {
		return year % dividend == 0;
	}

	bool is_leap_year(int year) {
		if (is_divisible(year, 4)) {
			if (is_divisible(year, 100)) {
				return is_divisible(year, 400);
			}
			return true;
		}
		return false;
	}
}  // namespace leap