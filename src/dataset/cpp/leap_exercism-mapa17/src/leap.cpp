#include "leap.h"

namespace leap{
    bool is_leap_year(int year){
        // By mentor pacmancoder
        return ((year % 100 != 0) || (year % 400 == 0)) && (year % 4 == 0);
        //return true;
        bool is_leap = false;

        if((year % 4) == 0)
            is_leap = true;

        if(is_leap && (year % 100 == 0))
            is_leap = false;

        if(!is_leap && (year % 400 == 0))
            is_leap = true;

        return is_leap;
    }
}