#ifndef CONVER_TIME2TM_H
#define CONVER_TIME2TM_H

#include <time.h>
#include <stdio.h>
#include <stdbool.h>

#define SECONDS_IN_MIN 60
#define SECONDS_IN_HOUR 3600
#define SECONDS_IN_DAY 86400
#define EPOCH 1970
#define TORONTO_OFFSET_IN_SECONDS 14400 


typedef struct tm_lk{ //custom struct tm
    int tm_sec;     //seconds past current minute
    int tm_min;     //minutes past current hour
    int tm_hour;    //hours past current day
    int tm_mday;    //days past current month
    int tm_mon;     //months past current year
    int tm_year;    //custom offset of years from 1970 - following tm_year from original struct tm

}tm_lk;


typedef long int time_lk;   //custom data type time_t: seconds from epoch 1970

bool is_leap_year(int year);
tm_lk *localtime_lk(time_lk *time);
void convert_time2yearmonthday(time_lk *time, int *year, int *month, int *day);


#endif