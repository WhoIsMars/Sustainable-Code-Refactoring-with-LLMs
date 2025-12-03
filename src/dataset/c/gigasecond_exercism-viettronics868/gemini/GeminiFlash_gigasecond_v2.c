#include "gigasecond.h"
#include <time.h>

#define GIGASECOND 1000000000

void gigasecond(time_t input, char *output, size_t size) {
  time_t gigasecond_time = input + GIGASECOND;
  struct tm timeinfo;

  // Use gmtime_r for thread safety and to avoid potential issues with static storage.
  gmtime_r(&gigasecond_time, &timeinfo);

  // Check if strftime will overflow the buffer.  If so, return early.
  if (size < 20) return;

  strftime(output, size, "%Y-%m-%d %H:%M:%S", &timeinfo);
}