#include "leap.h"

namespace leap {
	bool is_leap_year(int year) {
		return (year & 3) == 0 && (year % 100 != 0 || year % 400 == 0);
	}

	bool is_divisible(int year, int dividend){
		return year % dividend == 0;
	}
}  // namespace leap