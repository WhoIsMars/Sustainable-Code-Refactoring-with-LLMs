#include "clock.h"

#include <iostream>
#include <sstream>

using std::stringstream;

namespace date_independent {
clock clock::at(int hour, int minute) {
  int total_minutes = hour * 60 + minute;
  total_minutes = ((total_minutes % 1440) + 1440) % 1440;
  return clock(total_minutes / 60, total_minutes % 60);
}

clock clock::plus(int minutes) { 
  int total_minutes = hour * 60 + minute + minutes;
  total_minutes = ((total_minutes % 1440) + 1440) % 1440;
  return clock(total_minutes / 60, total_minutes % 60);
}

}  // namespace date_independent