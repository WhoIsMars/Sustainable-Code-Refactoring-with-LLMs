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
        int new_hour = _hour;

        if (new_min >= MIN_PER_DAY) {
            new_hour += new_min / 60;
            new_min %= 60;
        } else if (new_min < 0) {
            new_hour += (new_min / 60) - 1;
            new_min = new_min % 60 + MIN_PER_HOUR;
        }

        return clock(new_hour, new_min);
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
        char buffer[6];
        snprintf(buffer, sizeof(buffer), "%02d:%02d", _hour, _min);
        return std::string(buffer);
    }

}  // namespace date_independent