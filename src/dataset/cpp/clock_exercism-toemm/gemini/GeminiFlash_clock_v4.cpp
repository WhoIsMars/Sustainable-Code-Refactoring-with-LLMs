#include "clock.h"

#include <string>
#include <sstream>
#include <iomanip>

namespace date_independent {

    clock::clock(int hour, int min) {
        int total_minutes = (hour * 60 + min) % MIN_PER_DAY;
        if (total_minutes < 0) {
            total_minutes += MIN_PER_DAY;
        }
        _hour = total_minutes / 60;
        _min = total_minutes % 60;
    }

    clock clock::plus(int min) const {
        int new_min = _min + min;
        return clock(_hour, new_min);
    }

    clock clock::at(int hour, int min) {
        return clock(hour, min);
    }

    bool clock::operator==(const clock& rhs) const {
        return (_hour == rhs._hour) && (_min == rhs._min);
    }

    bool clock::operator!=(const clock& rhs) const {
        return !(*this == rhs);
    }

    clock::operator std::string() const {
        std::string hour_str = (_hour < 10 ? "0" : "") + std::to_string(_hour);
        std::string min_str = (_min < 10 ? "0" : "") + std::to_string(_min);
        return hour_str + ":" + min_str;
    }

}  // namespace date_independent