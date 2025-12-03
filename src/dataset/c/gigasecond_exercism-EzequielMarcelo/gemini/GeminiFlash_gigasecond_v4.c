#include "gigasecond.h"
#include <inttypes.h>

void gigasecond(time_t input, char *output, size_t size) {
    time_t gigasecond_after = input + GIGASECOND;

    struct tm timeinfo;
    struct tm *timeinfo_ptr = gmtime_r(&gigasecond_after, &timeinfo);

    if (timeinfo_ptr != NULL) {
        strftime(output, size, "%Y-%m-%d %H:%M:%S", &timeinfo);
    } else {
        output[0] = '\0';
    }
}