#include "clock.h"
#include <string>

namespace date_independent {
    constexpr int MINUTES_PER_DAY = 1440;
    
    clock::clock(const int hour, const int minute) noexcept {
        time_in_minutes = hour * 60 + minute;
        time_in_minutes = ((time_in_minutes % MINUTES_PER_DAY) + MINUTES_PER_DAY) % MINUTES_PER_DAY;
    }

    clock clock::at(const int hour, const int minute) {
        return clock(hour, minute);
    }

    clock clock::plus(int minute) {
        return clock(0, time_in_minutes + minute);
    }

    clock::operator std::string() const {
        const int hours = time_in_minutes / 60;
        const int mins = time_in_minutes % 60;
        
        std::string result;
        result.reserve(5);
        
        if (hours < 10) result += '0';
        result += std::to_string(hours);
        result += ':';
        if (mins < 10) result += '0';
        result += std::to_string(mins);
        
        return result;
    }
}