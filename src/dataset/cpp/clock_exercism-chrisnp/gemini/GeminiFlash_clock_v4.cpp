#include "clock.h"
#include <iomanip>
#include <sstream>

namespace {
constexpr int MINUTES_DAY = 1440;
constexpr int MINUTES_HOUR = 60;
} // namespace

date_independent::clock::clock(int ms) : minutes{normalize_minutes(ms)} {}

date_independent::clock date_independent::clock::at(int hours, int minutes) {
  return clock(hours * MINUTES_HOUR + minutes);
}

date_independent::clock date_independent::clock::plus(int ms) const noexcept {
  return clock(minutes + ms);
}

date_independent::clock date_independent::clock::minus(int ms) const noexcept {
  return clock(minutes - ms);
}

bool date_independent::clock::operator==(const clock &other) const noexcept {
  return minutes == other.minutes;
}

bool date_independent::clock::operator!=(const clock &other) const noexcept {
  return minutes != other.minutes;
}

date_independent::clock::operator std::string() const {
  int display_minutes = minutes % MINUTES_HOUR;
  int display_hours = minutes / MINUTES_HOUR;

  std::string result;
  result.reserve(5);
  result.push_back(static_cast<char>((display_hours / 10) + '0'));
  result.push_back(static_cast<char>((display_hours % 10) + '0'));
  result.push_back(':');
  result.push_back(static_cast<char>((display_minutes / 10) + '0'));
  result.push_back(static_cast<char>((display_minutes % 10) + '0'));
  return result;
}

int date_independent::clock::normalize_minutes(int ms) const noexcept {
  ms %= MINUTES_DAY;
  if (ms < 0) {
    ms += MINUTES_DAY;
  }
  return ms;
}