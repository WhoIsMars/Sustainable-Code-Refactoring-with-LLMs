#include "clock.h"
#include <stdio.h>
#include <stdbool.h>

clock_t clock_create(int hour, int minute) {
    clock_t clock;
    int h = hour % 24;
    if (h < 0) h += 24;
    int m = minute % 60;
    if (m < 0) m += 60;

    snprintf(clock.text, sizeof(clock.text), "%02d:%02d", h, m);
    return clock;
}

clock_t clock_add(clock_t clock, int minute_add) {
    int hour, minute;
    sscanf(clock.text, "%d:%d", &hour, &minute);
    return clock_create(hour, minute + minute_add);
}

clock_t clock_subtract(clock_t clock, int minute_subtract) {
    int hour, minute;
    sscanf(clock.text, "%d:%d", &hour, &minute);
    return clock_create(hour, minute - minute_subtract);
}

bool clock_is_equal(clock_t a, clock_t b) {
    return (strcmp(a.text, b.text) == 0);
}