#include "clock.h"
#include <string>
#include <array>

namespace {
constexpr int MINUTES_DAY = 1440;
constexpr int MINUTES_HOUR = 60;
} // namespace

date_independent::clock::clock(int ms) noexcept 
    : minutes((ms % MINUTES_DAY + MINUTES_DAY) % MINUTES_DAY) {}

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
    std::array<char, 6> buffer{};
    snprintf(buffer.data(), buffer.size(), "%02d:%02d", minutes / MINUTES_HOUR, minutes % MINUTES_HOUR);
    return std::string(buffer.data());
}