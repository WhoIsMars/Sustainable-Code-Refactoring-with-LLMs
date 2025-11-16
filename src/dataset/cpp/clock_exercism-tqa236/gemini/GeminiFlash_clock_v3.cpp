#include "clock.h"

#include <iostream>
#include <sstream>

using std::stringstream;

namespace date_independent {

clock clock::at(int hour, int minute) {
  int total_minutes = hour * 60 + minute;
  total_minutes %= (24 * 60);
  if (total_minutes < 0) {
    total_minutes += (24 * 60);
  }

  int exact_hour = total_minutes / 60;
  int exact_minute = total_minutes % 60;

  return clock(exact_hour, exact_minute);
}

clock clock::plus(int minutes) { return clock::at(hour, minute + minutes); }

}  // namespace date_independent