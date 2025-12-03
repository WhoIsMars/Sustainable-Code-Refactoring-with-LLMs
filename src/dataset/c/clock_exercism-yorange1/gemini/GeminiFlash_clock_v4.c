#include "clock.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MINUTES_PER_HOUR (60)
#define HOURS_PER_DAY (24)
#define MINUTES_PER_DAY (MINUTES_PER_HOUR * HOURS_PER_DAY)

static int normalize_minutes(int total_minutes) {
    total_minutes %= MINUTES_PER_DAY;
    if (total_minutes < 0) {
        total_minutes += MINUTES_PER_DAY;
    }
    return total_minutes;
}

static clock_t create_clock_from_minutes(int total_minutes) {
    total_minutes = normalize_minutes(total_minutes);

    int hour = total_minutes / MINUTES_PER_HOUR;
    int minute = total_minutes % MINUTES_PER_HOUR;

    clock_t clock;
    snprintf(clock.text, MAX_STR_LEN, "%02d:%02d", hour, minute);
    return clock;
}

clock_t clock_create(int hour, int minute) {
    int total_minutes = hour * MINUTES_PER_HOUR + minute;
    return create_clock_from_minutes(total_minutes);
}

clock_t clock_add(clock_t clock, int minute_add) {
    int hour, minute;
    if (sscanf(clock.text, "%d:%d", &hour, &minute) != 2) {
        clock_t invalid_clock = {"Invalid Clock"};
        return invalid_clock;
    }

    int total_minutes = hour * MINUTES_PER_HOUR + minute + minute_add;
    return create_clock_from_minutes(total_minutes);
}

clock_t clock_subtract(clock_t clock, int minute_subtract) {
    int hour, minute;
    if (sscanf(clock.text, "%d:%d", &hour, &minute) != 2) {
        clock_t invalid_clock = {"Invalid Clock"};
        return invalid_clock;
    }

    int total_minutes = hour * MINUTES_PER_HOUR + minute - minute_subtract;
    return create_clock_from_minutes(total_minutes);
}

bool clock_is_equal(clock_t a, clock_t b) {
    return (strncmp(a.text, b.text, MAX_STR_LEN) == 0);
}