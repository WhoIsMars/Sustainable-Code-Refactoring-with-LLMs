#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int hour;
    int minute;
    char text[6]; // HH:MM + null terminator
} clock_t;

clock_t clock_create(int hour, int minute) {
    clock_t clock;

    // Normalize hour and minute to be within 0-23 and 0-59 respectively
    hour = hour % 24;
    if (hour < 0) hour += 24; // Handle negative hours

    minute = minute % 60;
    if (minute < 0) minute += 60; // Handle negative minutes

    clock.hour = hour;
    clock.minute = minute;
    sprintf(clock.text, "%02d:%02d", hour, minute); // Use sprintf directly

    return clock;
}

clock_t clock_add(clock_t clock, int minute_add) {
    int total_minutes = clock.hour * 60 + clock.minute + minute_add;
    int new_hour = (total_minutes / 60) % 24;
    if (new_hour < 0) new_hour += 24;
    int new_minute = total_minutes % 60;
    if (new_minute < 0) new_minute += 60;

    return clock_create(new_hour, new_minute);
}

clock_t clock_subtract(clock_t clock, int minute_subtract) {
    return clock_add(clock, -minute_subtract); // Reuse clock_add for subtraction
}

bool clock_is_equal(clock_t a, clock_t b) {
    return (a.hour == b.hour && a.minute == b.minute); // Compare hour and minute directly
}