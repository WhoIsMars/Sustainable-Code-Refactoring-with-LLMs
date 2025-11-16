#include "clock.h"

#include <string>
#include <iomanip>

namespace date_independent {

    clock::clock(int hour, int min) : _hour(hour), _min(min) {
        // account for multiple days
        int total_min = (hour * 60 + min) % MIN_PER_DAY;

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
        return clock{hour, min};
    }

    bool clock::operator==(const clock& rhs) const {
        return (_hour == rhs._hour) && (_min == rhs._min);
    }

    bool clock::operator!=(const clock& rhs) const {
        return (_hour != rhs._hour) || (_min != rhs._min);
    }

    clock::operator std::string() const {
        std::string result;
        result.reserve(5); // "HH:MM"
        
        if (_hour < 10) result += '0';
        result += std::to_string(_hour);
        result += ':';
        if (_min < 10) result += '0';
        result += std::to_string(_min);
        
        return result;
    }

}  // namespace date_independent