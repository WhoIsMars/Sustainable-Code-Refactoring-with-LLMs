#include "clock.h"

#include <math.h>

#include <iostream>
#include <sstream>

using std::stringstream;

namespace date_independent {
clock clock::at(int hour, int minute) {
  auto exact_hour =
      ((hour + static_cast<int>(floor(minute / 60.0))) % 24 + 24) % 24;
  auto exact_minute = (minute % 60 + 60) % 60;
  return clock(exact_hour, exact_minute);
}

clock clock::plus(int minutes) { return clock::at(hour, minute + minutes); }

}  // namespace date_independent
