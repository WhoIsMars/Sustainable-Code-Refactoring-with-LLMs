#include "clock.h"

#include <iostream>
#include <sstream>

using std::stringstream;

namespace date_independent {
clock clock::at(int hour, int minute) {
  hour += minute / 60;
  minute %= 60;

  hour %= 24;
  if (hour < 0) {
    hour += 24;
  }
  if (minute < 0) {
    minute += 60;
  }

  return clock(hour, minute);
}

clock clock::plus(int minutes) { return clock::at(hour, minute + minutes); }

}  // namespace date_independent