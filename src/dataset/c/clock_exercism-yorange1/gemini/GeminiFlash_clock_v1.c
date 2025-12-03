#include "clock.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MINUTE_PER_HOUR (60)
#define HOUR_PER_DAY (24)
#define MINUTE_PER_DAY (MINUTE_PER_HOUR * HOUR_PER_DAY)

static clock_t minute_to_clock(int total_minute) {
    total_minute %= MINUTE_PER_DAY;
    if (total_minute < 0) {
        total_minute += MINUTE_PER_DAY;
    }

    int actual_hour = total_minute / MINUTE_PER_HOUR;
    int actual_minute = total_minute % MINUTE_PER_HOUR;

    clock_t clock;
    snprintf(clock.text, MAX_STR_LEN, "%02d:%02d", actual_hour, actual_minute);

    return clock;
}

clock_t clock_create(int hour, int minute) {
    int total_minute = hour * MINUTE_PER_HOUR + minute;
    return minute_to_clock(total_minute);
}

clock_t clock_add(clock_t clock, int minute_add) {
    int clock_hour;
    int clock_minute;

    if (sscanf(clock.text, "%d:%d", &clock_hour, &clock_minute) != 2) {
        clock_t error_clock;
        strncpy(error_clock.text, "Invalid Clock", MAX_STR_LEN);
        error_clock.text[MAX_STR_LEN - 1] = '\0';
        return error_clock;
    }

    int total_minute = clock_hour * MINUTE_PER_HOUR + clock_minute + minute_add;
    return minute_to_clock(total_minute);
}

clock_t clock_subtract(clock_t clock, int minute_subtract) {
    int clock_hour;
    int clock_minute;

    if (sscanf(clock.text, "%d:%d", &clock_hour, &clock_minute) != 2) {
        clock_t error_clock;
        strncpy(error_clock.text, "Invalid Clock", MAX_STR_LEN);
        error_clock.text[MAX_STR_LEN - 1] = '\0';
        return error_clock;
    }

    int total_minute = clock_hour * MINUTE_PER_HOUR + clock_minute - minute_subtract;
    return minute_to_clock(total_minute);
}

bool clock_is_equal(clock_t a, clock_t b) {
    return (strcmp(a.text, b.text) == 0);
}