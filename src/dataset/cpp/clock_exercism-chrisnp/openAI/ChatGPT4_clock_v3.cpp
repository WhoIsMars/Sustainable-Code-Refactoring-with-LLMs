#include "clock.h"
#include <string>
#include <array>

namespace {
constexpr int MINUTES_DAY = 1440;
constexpr int MINUTES_HOUR = 60;

std::string format_time(int total_minutes) {
    std::array<char, 6> buffer{};
    int hours = total_minutes / MINUTES_HOUR;
    int minutes = total_minutes % MINUTES_HOUR;
    snprintf(buffer.data(), buffer.size(), "%02d:%02d", hours, minutes);
    return std::string(buffer.data());
}
} // namespace

date_independent::clock::clock(int ms) 
    : minutes((ms % MINUTES_DAY + MINUTES_DAY) % MINUTES_DAY) {}

date_independent::clock 
date_independent::clock::at(int hours, int minutes) {
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
    return format_time(minutes);
}