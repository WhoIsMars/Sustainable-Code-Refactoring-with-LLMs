/*
this is a program that practice to create clock with the library time.h and strftime() and strptime() and mktime()
and localtime() and struct tm {} and time_t type

*/


#include "clocks_v.h"
#include "time_v.h"
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

clock_t create_clocks(double hour, double minute){

    clock_t cpy_clock;

    time_t from_epoch = time_v(NULL);

    tm_v *hour_min =  localtime_v(&from_epoch);
    
    if (hour_min == NULL){
        fprintf(stderr, "error getting localtime-description %s \n",strerror(errno));
        exit(EXIT_FAILURE);
    }
    hour_min->tm_hour = hour;
    hour_min->tm_min = minute;
    mktime_v(hour_min);

    if (strftime_v(cpy_clock.text, MAX_STR_LENG, "%H:%M", hour_min) == 0 ){
        fprintf(stderr, "error formatting time - description %s \n", strerror(errno));
        exit(EXIT_FAILURE);
    }
  

    return cpy_clock;
    
}


//using strptime and strftime to convert string to time and time to string
clock_t add_minute(clock_t clock, double minute){
    clock_t cpy_clock;
    
    strcpy(cpy_clock.text, clock.text);
    
    struct tm_v *hour_min = malloc(sizeof(struct tm_v));
    memset(hour_min, 0, sizeof(struct tm_v));
    
    strptime_v(cpy_clock.text, "%H:%M", hour_min);
    hour_min->tm_min += minute;
    mktime_v(hour_min);
    if (strftime_v(cpy_clock.text, MAX_STR_LENG, "%H:%M", hour_min) == 0){
        fprintf(stderr, "error formatting time - description %s \n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    free(hour_min);
    return cpy_clock;
}

bool clock_is_equal(clock_t a, clock_t b){
     return (strcmp(a.text, b.text) == 0);
 }

