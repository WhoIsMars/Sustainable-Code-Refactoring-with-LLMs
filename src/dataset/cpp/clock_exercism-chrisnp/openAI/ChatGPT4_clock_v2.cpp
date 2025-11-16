#include "clock.h"
#include <string>
#include <array>

namespace {
constexpr int MINUTES_DAY = 1440;
constexpr int MINUTES_HOUR = 60;

constexpr std::array<char, 10> DIGITS = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
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
    char buffer[6];
    int hours = minutes / MINUTES_HOUR;
    int mins = minutes % MINUTES_HOUR;
    buffer[0] = DIGITS[hours / 10];
    buffer[1] = DIGITS[hours % 10];
    buffer[2] = ':';
    buffer[3] = DIGITS[mins / 10];
    buffer[4] = DIGITS[mins % 10];
    buffer[5] = '\0';
    return std::string(buffer);
}