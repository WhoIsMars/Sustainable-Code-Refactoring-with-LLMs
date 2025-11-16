#include "clock.h"

#include <iostream>
#include <sstream>

using std::stringstream;

namespace date_independent {
clock clock::at(int hour, int minute) {
  int total_minutes = hour * 60 + minute;
  int normalized_minutes = ((total_minutes % 1440) + 1440) % 1440;
  int exact_hour = normalized_minutes / 60;
  int exact_minute = normalized_minutes % 60;
  return clock(exact_hour, exact_minute);
}

clock clock::plus(int minutes) { 
  int total_minutes = hour * 60 + minute + minutes;
  int normalized_minutes = ((total_minutes % 1440) + 1440) % 1440;
  int exact_hour = normalized_minutes / 60;
  int exact_minute = normalized_minutes % 60;
  return clock(exact_hour, exact_minute);
}

}  // namespace date_independent