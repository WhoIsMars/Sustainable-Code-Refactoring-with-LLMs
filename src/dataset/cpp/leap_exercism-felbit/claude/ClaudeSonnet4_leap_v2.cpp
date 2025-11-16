#include "leap.h"

namespace leap {
    bool is_leap_year(Year year)
    {
        return (year & 3) == 0 && (year % 100 != 0 || year % 400 == 0);
    }
}