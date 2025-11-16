#include "leap.h"

namespace {
    bool is_div(int n, int d)
    {
        return (n % d) == 0;
    }
};

/*
 * In the Gregorian calendar three criteria must be taken into
 * account to identify leap years:
 *   - The year can be evenly divided by 4;
 *   - If the year can be evenly divided by 100, it is NOT a leap year, unless;
 *   - The year is also evenly divisible by 400. Then it is a leap year.
 */

bool leap::is_leap_year(int year)
{
    if (is_div(year, 4)) {
        if (is_div(year, 100)) {
            return is_div(year, 400);
        }
        
        return true;
    }
    
    return false;
}
