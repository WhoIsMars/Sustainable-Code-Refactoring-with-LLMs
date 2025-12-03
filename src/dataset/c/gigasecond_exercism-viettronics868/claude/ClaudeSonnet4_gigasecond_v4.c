#include "gigasecond.h"
#include <time.h>

#define GIGASECOND 1000000000

void gigasecond(time_t input, char *output, size_t size) {
    time_t result_time = input + GIGASECOND;
    struct tm *time_info = gmtime(&result_time);
    strftime(output, size, "%Y-%m-%d %H:%M:%S", time_info);
}