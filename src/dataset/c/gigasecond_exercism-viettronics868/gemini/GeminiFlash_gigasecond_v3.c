#include "gigasecond.h"
#include <time.h>

#define GIGASECOND 1000000000

void gigasecond(time_t input, char *output, size_t size) {
  time_t gigasecond_time = input + GIGASECOND;
  struct tm timeinfo;

  struct tm *my_time = gmtime_r(&gigasecond_time, &timeinfo);

  if (my_time != NULL) {
    strftime(output, size, "%Y-%m-%d %H:%M:%S", my_time);
  } else {
    output[0] = '\0';
  }
}