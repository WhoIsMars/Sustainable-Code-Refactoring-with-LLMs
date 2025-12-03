#include "gigasecond.h"

void gigasecond(time_t input, char *output, size_t size) {
    time_t gigasecond_after = input + GIGASECOND;

    struct tm *timeinfo = gmtime(&gigasecond_after);

    strftime(output, size, "%Y-%m-%d %H:%M:%S", timeinfo);
}