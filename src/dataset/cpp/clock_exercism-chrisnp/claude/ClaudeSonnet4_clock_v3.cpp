#include "clock.h"
#include <string>

namespace {
constexpr int MINUTES_DAY { 1440 };
constexpr int MINUTES_HOUR { 60 };
} // namespace

date_independent::clock::clock(int ms) noexcept : minutes 
{ (ms % MINUTES_DAY + MINUTES_DAY) % MINUTES_DAY } {}

date_independent::clock 
date_independent::clock::at(int hours, int minutes) noexcept {
    return clock(hours * MINUTES_HOUR + minutes);
}

date_independent::clock 
date_independent::clock::plus(int ms) const noexcept {
    return clock(minutes + ms);
}

date_independent::clock 
date_independent::clock::minus(int ms) const noexcept {
    return clock(minutes - ms);
}

bool 
date_independent::clock::operator==(const clock &other) const noexcept {
    return minutes == other.minutes;
}

bool 
date_independent::clock::operator!=(const clock &other) const noexcept {
    return minutes != other.minutes;
}

date_independent::clock::operator std::string() const {
    const int hours = minutes / MINUTES_HOUR;
    const int mins = minutes % MINUTES_HOUR;
    
    std::string result;
    result.reserve(5);
    
    if (hours < 10) result += '0';
    result += std::to_string(hours);
    result += ':';
    if (mins < 10) result += '0';
    result += std::to_string(mins);
    
    return result;
}