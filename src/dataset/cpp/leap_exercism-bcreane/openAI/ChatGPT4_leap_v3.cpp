#include "leap.h"

namespace {
    inline bool is_div(int n, int d) noexcept
    {
        return (n % d) == 0;
    }
}

bool leap::is_leap_year(int year) noexcept
{
    return is_div(year, 4) && (!is_div(year, 100) || is_div(year, 400));
}