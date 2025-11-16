#include "leap.h"

namespace leap {

    bool is_leap_year(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    } 

    bool is_divisible_by(int num, int x) {
        return num % x == 0;
    }

}  // namespace leap