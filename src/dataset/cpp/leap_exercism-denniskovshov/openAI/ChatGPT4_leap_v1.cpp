#include "leap.h"

namespace leap {
    bool is_leap_year(int year) {
        if (year < 1) return false;

        if (year % 4 != 0) return false;
        if (year % 100 == 0 && year % 400 != 0) return false;

        return true;
    }
}  // namespace leap