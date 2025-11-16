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
        int new_minutes = _min + min;
        int new_hour = _hour;

        if (new_minutes >= MIN_PER_DAY) {
            new_hour += new_minutes / 60;
            new_minutes %= 60;
        } else if (new_minutes < 0) {
            new_hour += (new_minutes / 60) -1;
            new_minutes = new_minutes % 60 + MIN_PER_DAY;
        } else {
            new_hour += new_minutes / 60;
            new_minutes %= 60;
        }

        new_hour %= 24;
        if (new_hour < 0) {
            new_hour += 24;
        }

        return clock(new_hour, new_minutes);
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