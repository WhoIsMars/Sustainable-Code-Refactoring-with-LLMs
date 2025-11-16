#include "clock.h"

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

namespace date_independent {



    clock::clock(int hour, int min) : _hour(hour), _min(min) {

        // account for multiple days
        int total_min = (_hour * 60 + _min) % MIN_PER_DAY;

        if (total_min < 0) {
            total_min += MIN_PER_DAY;
        }

        _hour = total_min / 60;
        _min = total_min % 60;
    }

    clock clock::plus(int min) const {

        return clock(_hour, _min + min);
    
    }
    
    clock clock::at(int hour, int min) {

/*         // check for minutes rolling over to additional hours
        int min_rolling = min % 60;
        int rolling_ctr{min / 60};

        // add or subtract hours if minutes roll over
        hour += rolling_ctr;

        int hour_formatted{hour % 24};
        int min_formatted{min_rolling};

        // negative hours & minutes 
        if (hour < 0)
            hour_formatted += 24;
        if (min < 0) {
            min_formatted += 60;
            
            if (hour_formatted == 0) {     // midnight, subtract over midnight
                hour_formatted = 23;
            } else {
                hour_formatted--;       // otherwise, just go back 1 hour
            }
            
        } */


        return clock{hour, min};

    }

    bool clock::operator==(const clock& rhs) const {

        return (_hour == rhs._hour) && (_min == rhs._min);
    }

    bool clock::operator!=(const clock& rhs) const {

        return !operator==(rhs);
    }




    clock::operator std::string() const {

        std::ostringstream hour_stringstream;
        std::ostringstream min_stringstream;

        hour_stringstream << std::setw(2) << std::setfill('0') << _hour;
        min_stringstream << std::setw(2) << std::setfill('0') << _min;


        return hour_stringstream.str() + ":" + min_stringstream.str();
    }

}  // namespace date_independent
