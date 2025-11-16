#include "leap.h"

namespace leap {

    bool is_leap_year(int year) {
        if ( is_divisible_by(year, 400) ) {
            return true;
        }
        if ( is_divisible_by(year, 100) ) {
            return false;
        }
        if ( is_divisible_by(year, 4) ) {
            return true;
        }

        return false;
    } 

    bool is_divisible_by(int num, int x) {
        int remainder = num % x;
        return remainder == 0;
    }

}  // namespace leap
