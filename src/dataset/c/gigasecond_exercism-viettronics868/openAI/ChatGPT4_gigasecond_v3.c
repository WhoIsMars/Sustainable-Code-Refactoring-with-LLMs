#include "gigasecond.h"
#include <time.h>

#define GIGASECOND 1000000000

void gigasecond(time_t input, char *output, size_t size) {
    struct tm my_time;
    time_t cpy_input = input + GIGASECOND;
    gmtime_r(&cpy_input, &my_time);
    strftime(output, size, "%Y-%m-%d %H:%M:%S", &my_time);
}