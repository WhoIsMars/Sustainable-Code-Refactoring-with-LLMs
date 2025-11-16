#include "clock.h"

#include <string>
#include <sstream>
#include <iomanip>

namespace date_independent {

    constexpr int MIN_PER_DAY = 1440;

    clock::clock(int hour, int min) {
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
        return clock(hour, min);
    }

    bool clock::operator==(const clock& rhs) const {
        return _hour == rhs._hour && _min == rhs._min;
    }

    bool clock::operator!=(const clock& rhs) const {
        return !(*this == rhs);
    }

    clock::operator std::string() const {
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << _hour << ":"
            << std::setw(2) << std::setfill('0') << _min;
        return oss.str();
    }

}  // namespace date_independent