#include "leap.h"

namespace leap {
    bool is_leap_year(int year) {
        if (year < 1) [[unlikely]]
            return false;

        return (year & 3) == 0 && (year % 100 != 0 || year % 400 == 0);
    }
}  // namespace leap