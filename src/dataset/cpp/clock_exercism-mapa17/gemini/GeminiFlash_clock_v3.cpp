#include "clock.h"
#include <string>

namespace date_independent {
    using namespace std;

    clock::clock(const int hour, const int minute){
        constexpr int cx_minperday = 60 * 24;
        
        time_in_minutes = (hour * 60 + minute) % cx_minperday;
        if (time_in_minutes < 0) {
            time_in_minutes += cx_minperday;
        }
    }

    clock clock::at(const int hour, const int minute){
        return clock(hour, minute);
    }

    clock clock::plus(int minute){
        constexpr int cx_minperday = 60 * 24;
        int new_time = (time_in_minutes + minute) % cx_minperday;
        if (new_time < 0) {
            new_time += cx_minperday;
        }
        return clock(0, new_time);
    }

    clock::operator std::string() const {
        int hours = time_in_minutes / 60;
        int minutes = time_in_minutes % 60;

        char buffer[6];
        snprintf(buffer, sizeof(buffer), "%02d:%02d", hours, minutes);
        return std::string(buffer);
    }
}  // namespace date_independent