#include "leap.h"

namespace leap {

    inline bool is_divisible_by(int num, int x) {
        return num % x == 0;
    }

    bool is_leap_year(int year) {
        return (is_divisible_by(year, 400)) || 
               (is_divisible_by(year, 4) && !is_divisible_by(year, 100));
    }

}  // namespace leap