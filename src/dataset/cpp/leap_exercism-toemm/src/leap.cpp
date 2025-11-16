#include "leap.h"
#include <iostream>

namespace leap {



    bool is_leap_year(int year)
    {
        if (year % 4 == 0) 
        {
            if (year % 100 == 0 and year % 400 == 0)
            {
                return true;
            }
            else if (year % 100 == 0 and year % 400 != 0)
            {
                return false;
            }
            else {
                return true;
            }

        }
        else
        {
            return false;
        }
    

        
    }

}  // namespace leap
