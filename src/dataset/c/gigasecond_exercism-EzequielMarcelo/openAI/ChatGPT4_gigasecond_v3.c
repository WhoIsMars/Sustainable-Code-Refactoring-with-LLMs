#include "gigasecond.h"

void gigasecond(time_t input, char *output, size_t size) {
    const time_t gigasecond_after = input + GIGASECOND;

    struct tm timeinfo;
    gmtime_r(&gigasecond_after, &timeinfo);

    strftime(output, size, "%Y-%m-%d %H:%M:%S", &timeinfo);
}