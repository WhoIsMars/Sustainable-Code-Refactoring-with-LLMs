#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {
    using namespace std;

    clock::clock(int hour, int minute) {
        constexpr int minutes_per_day = 60 * 24;
        time_in_minutes = (hour * 60 + minute) % minutes_per_day;
        if (time_in_minutes < 0) {
            time_in_minutes += minutes_per_day;
        }
    }

    clock clock::at(int hour, int minute) {
        return clock(hour, minute);
    }

    clock clock::plus(int minute) {
        int new_minutes = time_in_minutes + minute;
        constexpr int minutes_per_day = 60 * 24;
        new_minutes %= minutes_per_day;
        if (new_minutes < 0) {
            new_minutes += minutes_per_day;
        }
        return clock(0, new_minutes);
    }

    clock::operator std::string() const {
        int hour = time_in_minutes / 60;
        int minute = time_in_minutes % 60;
        stringstream stream;
        stream << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute;
        return stream.str();
    }
}  // namespace date_independent