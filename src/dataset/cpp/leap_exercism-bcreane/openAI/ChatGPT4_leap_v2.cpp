#include "leap.h"

namespace {
    inline bool is_div(int n, int d) noexcept
    {
        return (n % d) == 0;
    }
}

/*
 * In the Gregorian calendar three criteria must be taken into
 * account to identify leap years:
 *   - The year can be evenly divided by 4;
 *   - If the year can be evenly divided by 100, it is NOT a leap year, unless;
 *   - The year is also evenly divisible by 400. Then it is a leap year.
 */

bool leap::is_leap_year(int year) noexcept
{
    return is_div(year, 4) && (!is_div(year, 100) || is_div(year, 400));
}