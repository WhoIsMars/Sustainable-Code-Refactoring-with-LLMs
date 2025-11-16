#include "leap.h"

bool leap::is_leap_year(int year) noexcept {
    return leap::divBy100(year) ? leap::divBy400(year) 
                                : leap::divBy004(year);
}
