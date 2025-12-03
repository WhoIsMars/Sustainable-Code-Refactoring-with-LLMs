/*
this is a program that practice to create clock with the library time.h and strftime() and strptime() and mktime()
and localtime() and struct tm {} and time_t type

*/
#define _XOPEN_SOURCE 700

#include "clocks.h"
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

struct clock_t create_clocks(double hour, double minute){

    struct clock_t cpy_clock;

    time_t from_epoch = time(NULL);
    struct tm *hour_min = localtime(&from_epoch);

    if (hour_min == NULL){
        fprintf(stderr, "error getting localtime-description %s \n",strerror(errno));
        exit(EXIT_FAILURE);
    }
    hour_min->tm_hour = hour;
    hour_min->tm_min = minute;
    mktime(hour_min);

    if (strftime(cpy_clock.text, MAX_STR_LENG, "%H:%M", hour_min) == 0 ){
        fprintf(stderr, "error formatting time - description %s \n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    

    return cpy_clock;
    
}


//using strptime and strftime to convert string to time and time to string
struct clock_t add_minute(struct clock_t clock, double minute){
    struct clock_t cpy_clock;

    strcpy(cpy_clock.text, clock.text);

    struct tm *hour_min = malloc(sizeof(struct tm));
    memset(hour_min, 0, sizeof(struct tm));

    strptime(cpy_clock.text, "%H:%M", hour_min);
    hour_min->tm_min += minute;
    mktime(hour_min);
    if (strftime(cpy_clock.text, MAX_STR_LENG, "%H:%M", hour_min) == 0){
        fprintf(stderr, "error formatting time - description %s \n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    free(hour_min);
    return cpy_clock;
}

bool clock_is_equal(struct clock_t a, struct clock_t b){
     return (strcmp(a.text, b.text) == 0);
 }

