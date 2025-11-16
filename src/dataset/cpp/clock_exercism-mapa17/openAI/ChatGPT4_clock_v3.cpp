#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {
    clock::clock(const int hour, const int minute) {
        constexpr int minutes_per_day = 1440; // 60 * 24
        time_in_minutes = ((hour * 60 + minute) % minutes_per_day + minutes_per_day) % minutes_per_day;
    }

    clock clock::at(const int hour, const int minute) {
        return clock(hour, minute);
    }

    clock clock::plus(int minute) {
        return clock(0, time_in_minutes + minute);
    }

    clock::operator std::string() const {
        std::ostringstream stream;
        stream << std::setw(2) << std::setfill('0') << (time_in_minutes / 60) << ":"
               << std::setw(2) << std::setfill('0') << (time_in_minutes % 60);
        return stream.str();
    }
}  // namespace date_independent