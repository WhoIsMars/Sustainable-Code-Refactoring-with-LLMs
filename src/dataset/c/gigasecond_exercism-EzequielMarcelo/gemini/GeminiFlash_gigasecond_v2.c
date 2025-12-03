#include "gigasecond.h"
#include <stdio.h> // Required for snprintf

void gigasecond(time_t input, char *output, size_t size) {
    time_t gigasecond_after = input + GIGASECOND;

    struct tm timeinfo; // Use a local struct to avoid potential race conditions with gmtime's static buffer
    struct tm *timeinfo_ptr = gmtime_r(&gigasecond_after, &timeinfo); // Use thread-safe gmtime_r

    if (timeinfo_ptr != NULL && size > 0) {
        snprintf(output, size, "%04d-%02d-%02d %02d:%02d:%02d",
                 timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday,
                 timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    } else if (size > 0) {
        output[0] = '\0'; // Ensure null termination in case of error
    }
}