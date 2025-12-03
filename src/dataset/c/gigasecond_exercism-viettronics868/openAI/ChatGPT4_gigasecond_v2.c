#include "gigasecond.h"
#include <time.h>

#define GIGASECOND 1000000000

void gigasecond(time_t input, char *output, size_t size) {
    struct tm my_time;
    time_t result_time = input + GIGASECOND;

    gmtime_r(&result_time, &my_time);
    strftime(output, size, "%Y-%m-%d %H:%M:%S", &my_time);
}