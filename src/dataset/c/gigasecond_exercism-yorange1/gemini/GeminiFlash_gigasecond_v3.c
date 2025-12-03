#include "gigasecond.h"
#include <limits.h>

time_t gigasecond_after(time_t now) {
  // Check for potential overflow before adding.
  if (now > (TIME_MAX - 1000000000)) {
    return TIME_MAX; // Or handle the overflow in a different way, e.g., return an error code.
  }
  return now + 1000000000;
}