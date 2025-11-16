#include "leap.h"

bool leap::is_leap_year(int year) noexcept {
    if (year % 4 != 0) return false;
    if (year % 100 == 0 && year % 400 != 0) return false;
    return true;
}