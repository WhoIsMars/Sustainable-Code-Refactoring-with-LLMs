#include "clock.h"

namespace date_independent {
clock clock::at(int hour, int minute) {
  int total_minutes = (hour * 60 + minute) % 1440;
  if (total_minutes < 0) total_minutes += 1440;
  return clock(total_minutes / 60, total_minutes % 60);
}

clock clock::plus(int minutes) { return clock::at(hour, minute + minutes); }

}  // namespace date_independent